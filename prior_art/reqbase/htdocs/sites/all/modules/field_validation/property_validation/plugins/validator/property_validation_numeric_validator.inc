<?php
/**
 * @file
 * Property validation numeric validator.
 *
 */
$plugin = array(
  'label' => t('Numeric values'),
  'description' => t('Verifies that user-entered values are numeric, with the option to specify min and / or max values.'),
  'handler' => array(
    'class' => 'property_validation_numeric_validator',
  ),
);

class property_validation_numeric_validator extends property_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value != '') {
      $flag = TRUE;
      if (!is_numeric($this->value)) {
        $flag = FALSE;
      }
      else{
        if (isset($settings['min']) && $settings['min'] != '' && $this->value < $settings['min']) {
          $flag = FALSE;
        }
        if (isset($settings['max']) && $settings['max'] != '' && $this->value > $settings['max']) {
          $flag = FALSE;
        }       
      }
      if (!$flag) {
        $token = array(
          '[min]' => isset($settings['min']) ? $settings['min'] : '',
          '[max]' => isset($settings['max']) ? $settings['max'] : '',
        );
        $this->set_error($token);
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['min'] = array(
      '#title' => t('Minimum value'),
      '#description' => t("Optionally specify the minimum value to validate the user-entered numeric value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum value'),
      '#description' => t("Optionally specify the maximum value to validate the user-entered numeric value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['max']) ? $default_settings['max'] : '',
    );
    parent::settings_form($form, $form_state);
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    $token_help = parent::token_help();
    $token_help += array(
      '[min]' => t('Minimum value'), 
      '[max]' => t('Maximum value'),
    );
    return $token_help;
  }
}