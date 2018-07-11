<?php
/**
 * @file
 * Field validation number of selections validator.
 *
 */
$plugin = array(
  'label' => t('Number of selections'),
  'description' => t('Verifies the number of options a user could select, with the option to specify minimum and maximum number of selections.'),
  'handler' => array(
    'class' => 'field_validation_number_of_selections_validator',
  ),
);

class field_validation_number_of_selections_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    $total_items = count($this->items);
    $flag = TRUE;

    if (isset($settings['min']) && $settings['min'] != '' && $total_items < $settings['min']) {
      $flag = FALSE;
    }
    if (isset($settings['max']) && $settings['max'] != '' && $total_items > $settings['max']) {
      $flag = FALSE;
    }       

    if (!$flag) {
      $token = array(
        '[min]' => isset($settings['min']) ? $settings['min'] : '',
        '[max]' => isset($settings['max']) ? $settings['max'] : '',
        '[count]' => $total_items,
      );
      $this->set_error($token);
    }
    //Do not need to validate other items.
    $break = TRUE;
    return $break;

  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['min'] = array(
      '#title' => t('Minimum number of selections'),
      '#description' => t("Optionally specify the minimum number of options a user should select."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum number of selections'),
      '#description' => t("Optionally specify the maximum number of options a user could select."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['max']) ? $default_settings['max'] : '',
    );
    parent::settings_form($form, $form_state);
  }
  
  /**
   * Return error element for the validation rule.
   */
  public function get_error_element() {
    $error_element = $this->rule->field_name . '][' . $this->langcode;
    return  $error_element;
  }

  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    $token_help = parent::token_help();
    $token_help += array(
      '[min]' => t('Minimum number of selections'), 
      '[max]' => t('Maximum number of selections'), 
      '[count]' => t('The real number of selections'),
    );
    return $token_help;
  }
}