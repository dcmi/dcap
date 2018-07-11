<?php
/**
 * @file
 * Basic class for property validation validator.
 *
 * All property validation validator classes should inherit this basic class.
 */

abstract class property_validation_validator {
  // Variables associated with validation.
  protected $entity_type;
  protected $entity;
  protected $field;
  protected $value;
  protected $rule;
  protected $errors;

  /**
   * Save arguments locally.
   */
  function __construct($entity_type = 'node', $entity = NULL, $value = '', $rule = NULL, &$errors = array()) {
    $this->entity_type = $entity_type;
    $this->entity = $entity;
    $this->value = $value;
    $this->rule = $rule;
    $this->errors = &$errors;
  }

  /**
   * Validate field. 
   */
  public function validate() {}

  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
  }
  /**
   * Return error message string for the validation rule.
   */
  public function get_error_message() {
    $error_message = $this->rule->error_message;
    return $error_message;
  }
  
  /**
   * Return error element for the validation rule.
   */
  public function get_error_element() {
    $error_element = $this->rule->property_name;
    return  $error_element;
  }
  
  /**
   * Return default settingsfor the validator.
   */
  public function get_default_settings(&$form, &$form_state) {
    $rule = isset($form_state['item']) ? $form_state['item'] : new stdClass();
    $default_settings = isset($rule->settings) ? $rule->settings : array();
    $default_settings = isset($form_state['values']['settings']) ? $form_state['values']['settings'] : $default_settings;
    return  $default_settings;
  }
  
  /**
   * Set error message.
   */
  public function set_error($tokens = array()) {
    $error_element = $this->get_error_element();
    $error_message = t($this->get_error_message());
    $tokens += array(
      '[entity-type]' => $this->rule->entity_type, 
      '[bundle]' => $this->rule->bundle, 
      '[property-name]' => $this->rule->property_name, 
      '[value]' => $this->value, 
    );
    $error_message = strtr($error_message, $tokens);
    form_set_error($error_element,  check_plain($error_message));
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    return array(
      '[entity-type]' => t('Machine name of entity type'), 
      '[bundle]' => t('Machine name of bundle'), 
      '[property-name]' => t('Name of current property'), 
      '[value]' => t('Current value to be validated on'),  
    );
  }
}