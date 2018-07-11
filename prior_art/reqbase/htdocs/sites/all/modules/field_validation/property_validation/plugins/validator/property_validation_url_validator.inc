<?php
/**
 * @file
 * Property validation url validator.
 *
 */
$plugin = array(
  'label' => t('URL'),
  'description' => t("Verifies that user-entered data is a valid url."),
  'handler' => array(
    'class' => 'property_validation_url_validator',
  ),
);

class property_validation_url_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
    $settings = $this->rule->settings;

    if ($this->value != '') {
      $flag = FALSE;
      if (empty($settings['external']) && empty($settings['internal'])) {
        $flag = TRUE;
      }

      if (!empty($settings['external'])) {
        $flag = valid_url($this->value, TRUE);
      }

      if (!$flag && !empty($settings['internal'])) {
        $normal_path = drupal_get_normal_path($this->value);
        if (!url_is_external($normal_path)) {
          $parsed_link = parse_url($normal_path); 
          if ($normal_path != $parsed_link['path']) {
            $normal_path = $parsed_link['path'];
          }
          $flag = drupal_valid_path($normal_path);
        }
      }
      
      if (!$flag) {
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
    $form['settings']['external'] = array(
      '#title' => t('External URL'),
      '#description' => t("Limit allowed input to absolute/external url."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['external']) ? $default_settings['external'] : FALSE,
    );
    $form['settings']['internal'] = array(
      '#title' => t('Internal path'),
      '#description' => t("Limit allowed input to internal drupal path."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['internal']) ? $default_settings['internal'] : FALSE,
    );
    $form['settings']['help'] = array(
      '#markup' => t("If both of External URL and Internal path are checked, it means that both of them are allowed."),
    );
    parent::settings_form($form, $form_state);
  }

}