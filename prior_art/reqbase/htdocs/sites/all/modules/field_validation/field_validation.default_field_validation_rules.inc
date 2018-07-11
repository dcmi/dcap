<?php

/**
 * @file
 * Provides default field validation rules
 */
 
/**
 * Implementation of hook_default_field_validation_rule().
 * 
 * Provide default validation rules.
 */
function field_validation_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass;
  $rule->disabled = TRUE;
  $rule->api_version = 2;
  $rule->name = 'body_min_words';
  $rule->rulename = 'Body Min words';
  $rule->field_name = 'body';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'page';
  $rule->validator = 'field_validation_words_validator';
  $rule->settings = array(
    'min' => '2',
    'max' => '',
  );
  $rule->error_message = t('You should enter at least two words.');
  $export['body_min_words'] = $rule;

  return $export;
}
