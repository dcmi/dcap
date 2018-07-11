<?php

/**
 * @file
 * A Ctools Export UI plugin for Field Validation rules.
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'field_validation_rule',
  'access' => 'administer site configuration',
  'menu' => array(
    'menu item' => 'field_validation',
    'menu prefix' => 'admin/structure',
    'menu title' => 'Field Validation',
    'menu description' => 'Administer Field Validation rules.',
  ),

  'title singular' => t('rule'),
  'title plural' => t('rules'),
  'title singular proper' => t('Field Validation rule'),
  'title plural proper' => t('Field Validation rules'),

  'form' => array(
    'settings' => 'field_validation_ui_ctools_export_ui_form',
    'validate' => 'field_validation_ui_ctools_export_ui_form_validate',
    'submit' => 'field_validation_ui_ctools_export_ui_form_submit',
  ),
);

/**
 * Define the add/edit form of validation rule.
 */
function field_validation_ui_ctools_export_ui_form(&$form, &$form_state) {
  ctools_include('export');
  $rule = $form_state['item'];
  $default_rulename = isset($rule->rulename) ? $rule->rulename : '';
  $default_entity_type = isset($rule->entity_type) ? $rule->entity_type : '';
  $default_bundle = isset($rule->bundle) ? $rule->bundle : '';
  $default_field_name = isset($rule->field_name) ? $rule->field_name : '';
  $default_col = isset($rule->col) ? $rule->col : '';
  $default_validator = isset($rule->validator) ? $rule->validator : '';
  $default_settings = isset($rule->settings) ? $rule->settings : array();
  $default_error_message = isset($rule->error_message) ? $rule->error_message : '';
  
  $default_rulename = isset($form_state['values']['rulename']) ? $form_state['values']['rulename'] : $default_rulename;
  $default_entity_type = isset($form_state['values']['entity_type']) ? $form_state['values']['entity_type'] : $default_entity_type;
  $default_bundle = isset($form_state['values']['bundle']) ? $form_state['values']['bundle'] : $default_bundle;
  $default_field_name = isset($form_state['values']['field_name']) ? $form_state['values']['field_name'] : $default_field_name;
  $default_col = isset($form_state['values']['col']) ? $form_state['values']['col'] : $default_col;
  $default_validator = isset($form_state['values']['validator']) ? $form_state['values']['validator'] : $default_validator;
  $default_settings = isset($form_state['values']['settings']) ? $form_state['values']['settings'] : $default_settings;
  $default_error_message = isset($form_state['values']['error_message']) ? $form_state['values']['error_message'] : $default_error_message;
  
  $form['rulename'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule name'),
    '#description' => t('The human-readable name of of this rule.'),
    '#default_value' => $rule->rulename,
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
  );
  
  $entity_type_options = array(
    '' => t('Choose an entity type'),
  );
  $entity_types = entity_get_info();
  foreach ($entity_types as $key => $entity_type) {
    if (!empty($entity_type['fieldable'])) {
      $entity_type_options[$key] = $entity_type['label'];
    }
  }
  $form['entity_type'] = array(
    '#type' => 'select',
    '#options' => $entity_type_options,
    '#title' => t('Entity type'),
    '#default_value' => $default_entity_type,
    '#required' => TRUE,
    '#ajax' => array(      
      'callback' => 'field_validation_ui_entity_type_callback',      
      'wrapper' => 'validation-rule-wrapper-div',      
      'method' => 'replace',      
      'effect' => 'fade',    
    ),
  );

  $bundle_options = array(
    '' => t('Choose a bundle'),
  );
  $bundles = !empty($entity_types[$default_entity_type]['bundles']) ? $entity_types[$default_entity_type]['bundles'] : array();
  foreach ($bundles as $key => $bundle) {
    $bundle_options[$key] = $bundle['label'];  
  }  
  $form['bundle'] = array(
    '#type' => 'select',
    '#options' => $bundle_options,
    '#title' => t('Bundle name'),
    '#default_value' => $default_bundle,
    '#required' => TRUE,
    '#ajax' => array(      
      'callback' => 'field_validation_ui_bundle_callback',      
      'wrapper' => 'validation-rule-wrapper-div',      
      'method' => 'replace',      
      'effect' => 'fade',    
    ),
  );

  $field_name_options = array(
    '' => t('Choose a field'),
  );
  $instances = array();
  if (!empty($default_entity_type) && !empty($default_bundle)) {
    $instances = field_info_instances($default_entity_type, $default_bundle);
  }

  foreach ($instances as $key => $instance) {
    $field_name_options[$key] = $instance['label'];  
  }
  if (!in_array($default_field_name, array_keys($field_name_options))) {
    $default_field_name = '';
  }  
  $form['field_name'] = array(
    '#type' => 'select',
    '#options' => $field_name_options,
    '#title' => t('Field name'),
    '#default_value' => $default_field_name,
    '#required' => TRUE,
    '#ajax' => array(      
      'callback' => 'field_validation_ui_field_name_callback',      
      'wrapper' => 'col-wrapper-div',      
      'method' => 'replace',      
      'effect' => 'fade',    
    ),
  ); 

  $field = field_info_field($default_field_name);
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

  if (!in_array($default_col, array_keys($col_options))) {
    $default_col = '';
  }   
  $form['col'] = array(
    '#type' => 'select',
    '#options' => $col_options,
    '#title' => t('Column'),
    '#description' => t('A column defined in the hook_field_schema() of this field.'),
    '#default_value' => $default_col,
    '#required' => TRUE,
    '#prefix' => '<div id="col-wrapper-div">',
    '#suffix' => '</div>',
  );
  
  $validator_options = array(
    '' => t('Choose a validator'),
  );
  ctools_include('plugins');
  $validators = ctools_get_plugins('field_validation', 'validator');
  //$validators = field_validation_get_validators();
  //print debug($validators);
  foreach ($validators as $validator_key => $validator) {
    $validator_options[$validator_key] = $validator['label'];
  }
  $form['validator'] = array(
    '#type' => 'select',
    '#options' => $validator_options,
    '#title' => t('Validator'),
    '#default_value' => $default_validator,
    '#required' => TRUE,
    //'#weight' => 3,
    '#ajax' => array(      
      'callback' => 'field_validation_ui_validator_callback',      
      'wrapper' => 'validation-rule-wrapper-div',      
      'method' => 'replace',      
      'effect' => 'fade',    
    ),
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#prefix' => '<div id="settings-wrapper-div">',
    '#suffix' => '</div>',
  );
  if (!empty($default_validator)) {
    $plugin = ctools_get_plugins('field_validation', 'validator', $default_validator);
    $class = ctools_plugin_get_class($plugin, 'handler');
    $validator_class = new $class();
    $validator_class->settings_form($form, $form_state);

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
  }
  /*
  $form['settings']['data'] = array(
    '#type' => 'textfield',
    '#title' => t('Config Data'),
    '#required' => FALSE,
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => isset($rule->settings['data']) ? $rule->settings['data'] : '',
    //'#weight' => 4,
  );
  */
  
  $form['error_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom error message'),
    '#description' => t("Specify an error message that should be displayed when user input doesn't pass validation"),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => $rule->error_message,
    '#weight' => 5,
  );

  $form['#prefix'] = '<div id="validation-rule-wrapper-div">';
  $form['#suffix'] = '</div>';
}

/**
 * Validation handler for the validation rule add/edit form.
 */
function field_validation_ui_ctools_export_ui_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (strlen($values['name']) > 32) {
    form_set_error('name', t('Name must be 32 characters or less in length.'));
  }
}
function field_validation_ui_ctools_export_ui_form_submit(&$form, &$form_state) {
  //$form_state['item']->settings['data'] = $form_state['values']['data'];
  //$form_state['item']->settings = $form_state['values']['settings'];
}

function field_validation_ui_entity_type_callback($form, &$form_state) {
  return $form;
}

function field_validation_ui_bundle_callback($form, &$form_state) {
  return $form;
}

function field_validation_ui_field_name_callback($form, &$form_state) {
  return $form['col'];
}

function field_validation_ui_validator_callback($form, &$form_state) {
  return $form;
}
