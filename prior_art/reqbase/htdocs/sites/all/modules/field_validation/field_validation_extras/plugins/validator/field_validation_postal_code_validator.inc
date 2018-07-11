<?php
/**
 * @file
 * Field validation postal code validator.
 *
 */
$plugin = array(
  'label' => t('Postal code'),
  'description' => t('Verifies that user-entered values are valid postal codes. This validator depend on Postal Code Validation module.'),
  'handler' => array(
    'class' => 'field_validation_postal_code_validator',
  ),
);

class field_validation_postal_code_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value !== '' && !is_null($this->value) && function_exists('postal_code_validation_validate')) {
      $country_code = isset($settings['country']) ? $settings['country'] : 'CN';
      //Address Field Module support
      if ($country_code == 'autodetect') {
        if (isset($this->item['country'])) {
          $country_code = $this->item['country'];
        }
      }
      $return = postal_code_validation_validate($this->value, $country_code);
      if (!empty($return['error'])) {
        $this->set_error();
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    include_once DRUPAL_ROOT . '/includes/locale.inc';
    $countries = country_get_list();
    $countries['autodetect'] = t('Autodetect country(Address Field Module support)');
    $form['settings']['country'] = array(
      '#title' => t('Country'),
      '#type' => 'select',
      '#options' => $countries, 
      '#default_value' => isset($default_settings['country']) ? $default_settings['country'] : 'CN',
    );
    parent::settings_form($form, $form_state);
  }
}