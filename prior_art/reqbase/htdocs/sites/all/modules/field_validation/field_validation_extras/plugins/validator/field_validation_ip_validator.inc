<?php
/**
 * @file
 * Field validation ip validator. The code is ported from symfony Validator.
 *
 */
$plugin = array(
  'label' => t('IP'),
  'description' => t('Verifies that user-entered values are IP address.'),
  'handler' => array(
    'class' => 'field_validation_ip_validator',
  ),
);

class field_validation_ip_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value !== '' && !is_null($this->value)) {
      $version = isset($settings['version']) ? $settings['version'] : '';
      switch ($version) {
        case '4':
          $flag = FILTER_FLAG_IPV4;
          break;

        case '6':
          $flag = FILTER_FLAG_IPV6;
          break;

        case '4_no_priv':
          $flag = FILTER_FLAG_IPV4 | FILTER_FLAG_NO_PRIV_RANGE;
          break;

        case '6_no_priv':
          $flag = FILTER_FLAG_IPV6 | FILTER_FLAG_NO_PRIV_RANGE;
          break;

        case 'all_no_priv':
          $flag = FILTER_FLAG_NO_PRIV_RANGE;
          break;

        case '4_no_res':
          $flag = FILTER_FLAG_IPV4 | FILTER_FLAG_NO_RES_RANGE;
          break;

        case '6_no_res':
          $flag = FILTER_FLAG_IPV6 | FILTER_FLAG_NO_RES_RANGE;
          break;

        case 'all_no_res':
          $flag = FILTER_FLAG_NO_RES_RANGE;
          break;

        case '4_public':
          $flag = FILTER_FLAG_IPV4 | FILTER_FLAG_NO_PRIV_RANGE | FILTER_FLAG_NO_RES_RANGE;
          break;

        case '6_public':
          $flag = FILTER_FLAG_IPV6 | FILTER_FLAG_NO_PRIV_RANGE | FILTER_FLAG_NO_RES_RANGE;
          break;

        case 'all_public':
          $flag = FILTER_FLAG_NO_PRIV_RANGE | FILTER_FLAG_NO_RES_RANGE;
          break;

        default:
          $flag = NULL;
          break;
        }

      if (!filter_var($this->value, FILTER_VALIDATE_IP, $flag)) {
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
    $form['settings']['version'] = array(
      '#title' => t('IP Version'),
      '#type' => 'select',
      '#options' => array(
        '4' => t('V4'),
        '6' => t('V6'),
        'all' => t('ALL'),
        '4_no_priv' => t('V4_NO_PRIV'),
        '6_no_priv' => t('V6_NO_PRIV'),
        'all_no_priv' => t('ALL_NO_PRIV'),
        '4_no_res' => t('V4_NO_RES'),
        '6_no_res' => t('V6_NO_RES'),
        'all_no_res' => t('ALL_NO_RES'),
        '4_public' => t('V4_ONLY_PUBLIC'),
        '6_public' => t('V6_ONLY_PUBLIC'),
        'all_public' => t('ALL_ONLY_PUBLIC'),
      ),  
      '#default_value' => isset($default_settings['version']) ? $default_settings['version'] : 'all',
    );
    parent::settings_form($form, $form_state);
  }

}