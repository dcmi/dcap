<?php
/**
 * @file
 * Basic class for field validation validator.
 *
 * All field validation validator classes should inherit this basic class.
 */

abstract class field_validation_validator {
  // Variables associated with validation.
  protected $entity_type;
  protected $entity;
  protected $field;
  protected $instance;
  protected $langcode;
  protected $items;
  protected $delta;
  protected $item;
  protected $value;
  protected $rule;
  protected $errors;

  /**
   * Save arguments locally.
   */
  function __construct($entity_type = 'node', $entity = NULL, $field = '', $instance = NULL, $langcode = 'und', $items = array(), $delta = 0, $item = array(), $value = '', $rule = NULL, &$errors = array()) {
    $this->entity_type = $entity_type;
    $this->entity = $entity;
    $this->field = $field;
    $this->instance = $instance;
    $this->langcode = $langcode;
    $this->items = $items;
    $this->delta = $delta;
    $this->item = $item;
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
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['bypass'] = array(
      '#title' => t('Bypass validation'),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['bypass']) ? $default_settings['bypass'] : FALSE,
    );
    $roles_options = user_roles();
    $form['settings']['roles'] = array(
      '#title' => t('Roles'),
      '#description' => t("Only the checked roles will be able to bypass this validation rule."),
      '#type' => 'checkboxes',
      '#options' => $roles_options,
      '#default_value' => isset($default_settings['roles']) ? $default_settings['roles'] : array(),
      '#states' => array(
        'visible' => array(
          ':input[name="settings[bypass]"]' => array('checked' => TRUE),
        ), 
      ),
    );
    $form['settings']['errors'] = array(
      '#title' => t('Set errors using field API'),
      '#description' => t("There are two methods to set error: using form_set_error provided by form api, using errors provided by field api. form_set_error does not work correctly when a sub form embed into another form. errors does not work correctly when current field does not support hook_field_widget_error."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['errors']) ? $default_settings['errors'] : FALSE,
    );
    $form['settings']['condition'] = array(
      '#title' => t('Conditional validation'),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['condition']) ? $default_settings['condition'] : FALSE,
    );
    $form['settings']['condition_wrapper'] = array(
      '#type' => 'fieldset',
      //'#collapsible' => TRUE,
      '#collapsed' => FALSE,
	  //'#tree' => TRUE,
	  //'#title' => t('Replacement patterns'),
      '#states' => array(
        'visible' => array(
          ':input[name="settings[condition]"]' => array('checked' => TRUE),
        ), 
      ),
    );
    $form['settings']['condition_wrapper']['condition_field'] = array(
      '#title' => t('Condition field'),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['condition_wrapper']['condition_field']) ? $default_settings['condition_wrapper']['condition_field'] : '',
    );
    $operator_options = array(
      'equals' => t('equals'),
      'not_equals' => t('not equals'),
      'greater_than' => t('greater than'),
      'less_than' => t('less than'),
      'greater_or_equal' => t('greater or equal'),
      'less_or_equal' => t('less or equal'),
	);
    $form['settings']['condition_wrapper']['condition_operator'] = array(
      '#type' => 'select',
      '#options' => $operator_options,
      '#default_value' => isset($default_settings['condition_wrapper']['condition_operator']) ? $default_settings['condition_wrapper']['condition_operator'] : '',

    );
    $form['settings']['condition_wrapper']['condition_value'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['condition_wrapper']['condition_value']) ? $default_settings['condition_wrapper']['condition_value'] : '',
    );	
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
    $error_element = $this->rule->field_name . '][' . $this->langcode . '][' . $this->delta . '][' . $this->rule->col;
    // Support free tagging.
    if (!empty($this->field['type']) && $this->field['type'] == 'taxonomy_term_reference') {
      $error_element = $this->rule->field_name . '][' . $this->langcode;
    }
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
      '[field-name]' => $this->instance['label'], 
      '[value]' => $this->value, 
    );
    $error_message = field_filter_xss(strtr($error_message, $tokens));
    //We support two methods to set error: using form_set_error provided by form api, using errors provided by field api.
    //form_set_error does not work correctly when a sub form embed into another form; 
    //errors does not work correctly when current field does not support hook_field_widget_error.
    if (empty($this->rule->settings['errors'])) {
      form_set_error($error_element, $error_message);
    }
    else{
      $this->errors[$this->rule->field_name][$this->langcode][$this->delta][] = array(
        'error' => $this->rule->col,
        'message' => $error_message,
      );
    }
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    return array(
      '[entity-type]' => t('Machine name of entity type'), 
      '[bundle]' => t('Machine name of bundle'), 
      '[field-name]' => t('User readable name of current field'), 
      '[value]' => t('Current value to be validated on'),  
    );
  }
  
  /**
   * Bypass validation.
   */
  public function bypass_validation() {
    global $user;
    if (!empty($this->rule->settings['bypass']) && !empty($this->rule->settings['roles'])) {
      $roles = array_filter($this->rule->settings['roles']);
      $user_roles = array_keys($user->roles);
      foreach ($roles as $role) {
        if (in_array($role, $user_roles)) {
          return TRUE;
        }
      }
    }
    return FALSE;
  }
  
  /**
   * Get token type.
   */ 
  public function get_token_type() {
    $mappings = token_get_entity_mapping('entity');
	//print debug($mappings);
    $token_type = isset($mappings[$this->entity_type]) ? $mappings[$this->entity_type] : "";
    return $token_type;
  }
  
  /**
   * pass condition.
   */
  public function pass_condition() {
    $settings = $this->rule->settings;
    //print debug($settings);
    if (!empty($settings['condition'])) {
	  $condition_field = "";
      if (isset($settings['condition_wrapper']['condition_field']) && $settings['condition_wrapper']['condition_field'] != '' ) {
        $condition_field = token_replace($settings['condition_wrapper']['condition_field'], array($this->get_token_type() => $this->entity));
      }
	  $condition_operator = "equals";
      if (isset($settings['condition_wrapper']['condition_operator']) && $settings['condition_wrapper']['condition_operator'] != '' ) {
        $condition_operator = $settings['condition_wrapper']['condition_operator'];
      }
	  $condition_value = "";
      if (isset($settings['condition_wrapper']['condition_value']) && $settings['condition_wrapper']['condition_value'] != '' ) {
        $condition_value = token_replace($settings['condition_wrapper']['condition_value'], array($this->get_token_type() => $this->entity));
      }
      switch ($condition_operator){
        case 'equals':
          return $condition_field == $condition_value;
          break;  
        case 'not_equals':
          return $condition_field != $condition_value;
          break;
        case 'greater_than':
          return $condition_field > $condition_value;
          break;  
        case 'less_than':
          return $condition_field != $condition_value;
          break;
        case 'greater_or_equal':
          return $condition_field >= $condition_value;
          break;  
        case 'less_or_equal':
          return $condition_field <= $condition_value;
          break;		  
      }  
      return FALSE;
    }
    return TRUE;
  }
}