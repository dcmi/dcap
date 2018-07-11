<?php

/**
 * @file
 * Manages validation rules administration UI
 */
 
/**
 * Menu callback function using to dispatch.
 */
function field_validation_ui_callback_dispatch($instance, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {
  $output = '';
  if (empty($arg1)) {
    drupal_set_title(t('Validation'));
    $output .= field_validation_ui_manage($instance);
  }
  elseif ($arg1 == 'add') {
    drupal_set_title(t('Add validation'));
    $form = drupal_get_form('field_validation_ui_manage_rule', $instance, 'add', $arg2);
    $output .= drupal_render($form);
  }
  elseif ($arg1 == 'edit') {
    drupal_set_title(t('Edit rule'));
    $form = drupal_get_form('field_validation_ui_manage_rule', $instance, 'edit', $arg2, $arg3);
    $output .= drupal_render($form);
  }
  elseif ($arg1 == 'delete') {
    drupal_set_title(t('Delete rule'));
    $form = drupal_get_form('field_validation_ui_delete_rule', $arg2);
    $output .= drupal_render($form);
  }
  elseif ($arg1 == 'overwrite') {
    drupal_set_title(t('Overwrite rule'));
    $form = drupal_get_form('field_validation_ui_manage_rule', $instance, 'edit', $arg2, $arg3);
    $output .= drupal_render($form);
  }
  else{
    drupal_set_title(t('Validation'));
    $output .= field_validation_manage($instance);
  }

  return $output;
}

/**
 * Menu callback function to show an overview of the existing validation rules, and the option to add a rule
 */
function field_validation_ui_manage($instance) {
  $output = '';
  //$rules = field_validation_get_field_rules($instance);
  
  $bundle = $instance['bundle'];
  $entity_type = $instance['entity_type'];
  $field_name = $instance['field_name'];
  ctools_include('export');
  $rules = ctools_export_load_object('field_validation_rule', 'conditions', array('entity_type' => $entity_type, 'bundle' => $bundle, 'field_name' => $field_name));

  $output .= theme('field_validation_ui_manage_overview', array('rules' => $rules, 'instance' => $instance));
  $output .= theme('field_validation_ui_manage_add_rule', array('instance' => $instance));
  return $output;
}


/**
 * Callback function to add or edit a validation rule
 */
function field_validation_ui_manage_rule($form, $form_state, $instance, $action = 'add', $validator = 'regex', $ruleid = NULL) {
 // $form = array();
  //$rule_validator = field_validation_get_validator_info($validator);
  $rule_validator = array();
  if ($action == 'overwrite') {
    $rule = field_validation_ui_rule_load($ruleid);
  }
  elseif ($action == 'edit') {
    $rule = field_validation_ui_get_rule($ruleid);
  }
  else{
    $rule = new stdClass();
  }
  $form_state['item'] = $rule;

  $form['validator'] = array(
    '#type' => 'hidden',
    '#value' => $validator,
  );

  $form['action'] = array(
    '#type' => 'hidden',
    '#value' => $action,
  );

  if ($action == 'edit' && $rule) {
    $form['ruleid'] = array(
      '#type' => 'hidden',
      '#value' => $rule->ruleid,
    );

    $form['field_name'] = array(
      '#type' => 'hidden',
      '#value' => $rule->field_name,
    );

    $form['entity_type'] = array(
      '#type' => 'hidden',
      '#value' => $rule->entity_type,
    );

    $form['bundle'] = array(
      '#type' => 'hidden',
      '#value' => $rule->bundle,
    );
  }
  else {
    $form['field_name'] = array(
      '#type' => 'hidden',
      '#value' => $instance['field_name'],
    );

    $form['entity_type'] = array(
      '#type' => 'hidden',
      '#value' => $instance['entity_type'],
    );

    $form['bundle'] = array(
      '#type' => 'hidden',
      '#value' => $instance['bundle'],
    );
  }

  $form['rulename'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule name'),
    '#default_value' => (isset($rule->rulename)) ? $rule->rulename : '',
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#weight' => 1,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => (isset($rule->name)) ? $rule->name : '',
    '#machine_name' => array(
      'exists' => 'field_validation_ui_rule_load',
      'source' => array('rulename'),
    ),
    '#weight' => 2,
    '#maxlength' => 32,
  );
  $field = field_info_field($instance['field_name']);
  $col_options = array(
    '' => t('Choose a column'),
  );
  $columns = !empty($field['columns']) ? $field['columns'] : array();
  foreach ($columns as $key => $column) {
    $col_options[$key] = $key;  
  }

  // Support free tagging.
  if ($field['type'] == 'taxonomy_term_reference') {
    $col_options['name'] = 'name';
  }

  $form['col'] = array(
    '#type' => 'select',
    '#options' => $col_options,
    '#title' => t('Column'),
    '#description' => t('A column defined in the hook_field_schema() of this field.'),
    '#default_value' => (isset($rule->col)) ? $rule->col : '',
    '#required' => TRUE,
    '#weight' => 3,
  );

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#weight' => 4,
  );
  
  ctools_include('plugins');
  $plugin = ctools_get_plugins('field_validation', 'validator', $validator);
  $class = ctools_plugin_get_class($plugin, 'handler');
  $entity_type = $instance['entity_type'];
  $validator_class = new $class($entity_type);
  $validator_class->settings_form($form, $form_state);

  $form['error_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom error message'),
    '#description' => t("Specify an error message that should be displayed when user input doesn't pass validation"),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => isset($rule->error_message) ? $rule->error_message : '',
    '#weight' => 5,
  );

  $output = '<p>' . t('The following tokens are available for error message.' . '</p>');
  $token_help = $validator_class->token_help();
  if (!empty($token_help)) {
    $items = array();
    foreach ($token_help as $key => $value) {
      $items[] = $key . ' == ' . $value;
    }
    $output .= theme('item_list',
      array(
        'items' => $items,
      ));
  }

  $form['token_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => $output,
    '#id' => 'error-message-token-help',
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    '#weight' => 6,
  );
  
	if (module_exists("token")) {  
    $mappings = token_get_entity_mapping('entity');
	//print debug($mappings);
    $token_type = isset($mappings[$instance['entity_type']]) ? $mappings[$instance['entity_type']] : "";	
      $form['token_help']['tokens'] = array(
        '#theme' => 'token_tree',
        '#token_types' => array($token_type),
      );
    }
	
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => (isset($rule->ruleid)) ? t('Save rule') : t('Add rule'),
    '#weight' => 25,
  );
  
  if ($action == 'overwrite') {
    $form['submit']['#value'] = t('Overwrite rule');
  }

  return $form;
}

/**
 * Validation handler to add / edit a rule
 */
function field_validation_ui_manage_rule_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['action'] == 'edit') {
    if (!is_numeric($values['ruleid']) || $values['ruleid'] == 0) {
      form_set_error(NULL, t('A problem occurred while editing this rule. Please try again.'));
    }
  }
}


/**
 * Submit handler to add / edit a rule
 */
function field_validation_ui_manage_rule_submit($form, &$form_state) {
  $values = $form_state['values'];

  if ($values['action'] == 'add' || $values['action'] == 'overwrite') {
    drupal_write_record('field_validation_rule', $values);
  }

  if ($values['action'] == 'edit') {
    drupal_write_record('field_validation_rule', $values, 'ruleid');
  }
}

/**
 * Confirmation form to delete a rule
 */
function field_validation_ui_delete_rule($form, &$form_state, $ruleid) {
  $rule = new stdClass();
  if (isset($ruleid) && $ruleid > 0) {
    $rule = field_validation_ui_get_rule($ruleid);
    $form['ruleid'] = array(
      '#type' => 'hidden',
      '#value' => $ruleid,
    );
  }

  if (empty($rule)) {
    $source_path = isset($_GET['destination']) ? $_GET['destination']:"";
    drupal_goto($source_path);
  }

  return confirm_form($form,
    t('Are you sure you want to delete the rule %name?', array('%name' => $rule->rulename)),
    isset($_GET['destination']) ? $_GET['destination'] : $_GET['q'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler to delete a rule
 */
function field_validation_ui_delete_rule_submit($form, &$form_state) {
  $ruleid = $form_state['values']['ruleid'];
  db_delete('field_validation_rule')
    ->condition('ruleid', $ruleid)
    ->execute();
}

/**
 * Load a validation rule.
 *
 * @param $name
 *   This validation rule's name value.
 * @return
 *   An array of options for the specified validation rule.
 */
function field_validation_ui_rule_load($name) {
  // Use Ctools export API to fetch this rule.
  ctools_include('export');
  $result = ctools_export_load_object('field_validation_rule', 'names', array($name));
  if (isset($result[$name])) {
    return $result[$name];
  }
}

/**
 * Get a rule entry
 */
function field_validation_ui_get_rule($ruleid) {
  $result = db_query("SELECT * FROM {field_validation_rule} WHERE ruleid = :ruleid", array(':ruleid' => $ruleid), array('fetch' => PDO::FETCH_OBJ));
  $rule = $result->fetchObject();
  $rule->settings = unserialize($rule->settings);
  return $rule;
}

/**
 * Theme the 'add rule' list
 */
function theme_field_validation_ui_manage_add_rule($variables) {
  $instance = $variables['instance'];
  $output = '';
  //$validators = field_validation_get_validators();
  ctools_include('plugins');
  $validators = ctools_get_plugins('field_validation', 'validator');
  //print debug($instance);
  if ($validators) {
    $output = '<h3>' . t('Add a validation rule') . '</h3>';
    $output .= '<dl>';
    foreach ($validators as $validator_key => $validator_info) {
      $item = '';
      $path = isset($_GET['q']) ? $_GET['q'] : '';
      $url = $path . '/add/' . $validator_key;
      $item = '<dt>' . l($validator_info['label'], $url, array("query" => drupal_get_destination())) . '</dt>';
      $item .= '<dd>';
      if (!empty($validator_info['description'])) {
        $item .= $validator_info['description'] . ' ';
      }
      $item .= '</dd>';
      $output .= $item;
    }
    $output .= '</dl>';
  }
  return $output;
}


/**
 * Themable function to list the rules assigned to a field instance
 */
function theme_field_validation_ui_manage_overview($variables) {
  $rules = $variables['rules'];
  $instance = $variables['instance'];

  $header = array(t('Rule name'), t('Validator'), array(
      'data' => t('Operations'),
      'colspan' => 2,
    ));
  ctools_include('plugins');
  $validators = ctools_get_plugins('field_validation', 'validator');
  if (!empty($rules)) {
    foreach ($rules as $rule) {
      $row = array();
      $row[] = array(
        'data' => $rule->rulename,
      );
      $row[] = array(
        'data' => $validators[$rule->validator]['label'],
      );
      $path = isset($_GET['q']) ? $_GET['q'] : '';
      if (!empty($rule->ruleid)) {
        $row[] = array(
          'data' => l(t('Edit'), $path . '/edit/' . $rule->validator . '/' . $rule->ruleid, array("query" => drupal_get_destination())),
        );
        $row[] = array(
          'data' => l(t('Delete'), $path . '/delete/' . $rule->ruleid, array("query" => drupal_get_destination())),
        );
      }
      else{
        $row[] = array(
          'data' => l(t('Overwrite'), $path . '/overwrite/' . $rule->validator . '/' . $rule->name, array("query" => drupal_get_destination())),
          'colspan' => 2,
        );
      }
      $rows[] = $row;
    }
  }
  else {
    $rows[][] = array(
      'data' => t('No validation rules available.'),
      'colspan' => 5,
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}