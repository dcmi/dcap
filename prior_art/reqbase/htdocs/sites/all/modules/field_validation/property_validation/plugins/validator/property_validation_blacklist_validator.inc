<?php
/**
 * @file
 * Property validation blacklist validator.
 *
 */
$plugin = array(
  'label' => t('Words blacklist'),
  'description' => t("Validates that user-entered data doesn't contain any of the specified illegal words."),
  'handler' => array(
    'class' => 'property_validation_blacklist_validator',
  ),
);

class property_validation_blacklist_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    $blacklist = explode(',', $settings['data']);
    $blacklist = array_map('trim', $blacklist);
    $blacklist_regex = implode('|', $blacklist);
    if ($this->value != '' && (preg_match("/$blacklist_regex/i", $this->value))) {
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
      '#title' => t('Blacklisted words'),
      '#description' => t("Specify illegal words, seperated by commas. Make sure to escape reserved regex characters with an escape (\) character."),
      '#type' => 'textarea',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }

}