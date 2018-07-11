<?php
/**
 * @file
 * Field validation length validator.
 *
 */
$plugin = array(
  'label' => t('Length'),
  'description' => t('Verifies the length of user-entered values, with the option to specify minimum and maximum length.'),
  'handler' => array(
    'class' => 'field_validation_length_validator',
  ),
);

class field_validation_length_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value != '') {
      $flag = TRUE;
      $length = drupal_strlen($this->value);
      if (isset($settings['min']) && $settings['min'] != '') {
        $min = token_replace($settings['min'], array($this->get_token_type() => $this->entity));
		if ($length < $min) {
          $flag = FALSE;
        }
      }
      if (isset($settings['max']) && $settings['max'] != '') {
        $max = token_replace($settings['max'], array($this->get_token_type() => $this->entity));
		if ($length > $max) {
          $flag = FALSE;
        }
      }       

      if (!$flag) {
        $token = array(
          '[min]' => isset($min) ? $min : '',
          '[max]' => isset($max) ? $max : '',
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