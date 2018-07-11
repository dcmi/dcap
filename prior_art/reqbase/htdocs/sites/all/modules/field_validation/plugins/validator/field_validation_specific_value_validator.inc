<?php
/**
 * @file
 * Field validation specific value validator.
 *
 */
$plugin = array(
  'label' => t('Specific value(s)'),
  'description' => t("Verifies that the specified field contains a defined value."),
  'handler' => array(
    'class' => 'field_validation_specific_value_validator',
  ),
);

class field_validation_specific_value_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    $specific_values = explode(',', $settings['data']);
    $specific_values = array_map('trim', $specific_values);
    if ($this->value != '' && (!in_array($this->value, $specific_values))) {
      $this->set_error();
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('(Key) value'),
      '#description' => t("Specify the specific value(s) you want the field to contain. Separate multiple options by a comma. For fields that have keys, use the key value instead."),
      '#type' => 'textarea',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }

}