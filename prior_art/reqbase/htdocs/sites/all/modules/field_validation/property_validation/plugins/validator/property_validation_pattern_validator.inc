<?php
/**
 * @file
 * Property validation pattern validator.
 *
 */
$plugin = array(
  'label' => t('Pattern(regex lite)'),
  'description' => t('Verifies that a user-entered value conforms to a specified pattern.'),
  'handler' => array(
    'class' => 'property_validation_pattern_validator',
  ),
);

class property_validation_pattern_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
  
    // Following code was copied from http://drupal.org/node/1082134, thanks to DrewMathers
    if ($this->value != '') {
      $pattern =  $this->rule->settings['pattern'];
      $pattern = preg_quote($pattern, "/"); // Escape regex control characters
      If (PHP_VERSION < 5.3) { 
        $pattern = preg_replace('/-/', '\-', $pattern); // PHP bug #47229
      }
      $pattern = preg_replace('/a/', '[a-zA-Z]', $pattern);
      $pattern = preg_replace('/9/', '[0-9]', $pattern);
      $pattern = preg_replace('/#/', '[a-zA-Z0-9]', $pattern);
      if (!preg_match('/^(' . $pattern . ')$/', $this->value)) {
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
    $form['settings']['pattern'] = array(
      '#title' => t('Pattern'),
      '#description' => t("Specify a pattern where:") 
      . theme('item_list', array('items' => array(t('a - Represents an alpha character [a-zA-Z]'), t('9 - Represents a numeric character [0-9]'), t('# - Represents an alphanumeric character [a-zA-Z0-9]'))))
      . t('Example, North American phone number: (999) 999-999'),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['pattern']) ? $default_settings['pattern'] : '',
    );
    parent::settings_form($form, $form_state);
  }

}