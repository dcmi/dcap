<?php
/**
 * @file
 * property validation length validator.
 *
 */
$plugin = array(
  'label' => t('Length'),
  'description' => t('Verifies the length of user-entered values, with the option to specify minimum and maximum length.'),
  'handler' => array(
    'class' => 'property_validation_length_validator',
  ),
);

class property_validation_length_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value != '') {
      $flag = TRUE;
      $length = drupal_strlen($this->value);
      if (isset($settings['min']) && $settings['min'] != '' && $length < $settings['min']) {
        $flag = FALSE;
      }
      if (isset($settings['max']) && $settings['max'] != '' && $length > $settings['max']) {
        $flag = FALSE;
      }       

      if (!$flag) {
        $token = array(
          '[min]' => isset($settings['min']) ? $settings['min'] : '',
          '[max]' => isset($settings['max']) ? $settings['max'] : '',
          '[length]' => $length,
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
      '#title' => t('Minimum length'),
      '#description' => t("Optionally specify the minimum length to validate the user-entered value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum length'),
      '#description' => t("Optionally specify the maximum length to validate the user-entered value against."),
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
      '[min]' => t('Minimum length'), 
      '[max]' => t('Maximum length'), 
      '[length]' => t('Real length'),
    );
    return $token_help;
  }
}