<?php

/**
 * @file
 * Provides default property validation rules
 */
 
/**
 * Implementation of hook_default_property_validation_rule().
 * 
 * Provide default validation rules.
 */
function property_validation_default_property_validation_rule() {
  $export = array();

  $rule = new stdClass;
  $rule->disabled = TRUE;
  $rule->api_version = 2;
  $rule->name = 'title_min_words';
  $rule->rulename = 'Title Min words';
  $rule->property_name = 'title';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'page';
  $rule->validator = 'property_validation_words_validator';
  $rule->settings = array(
    'min' => '2',
    'max' => '',
  );
  $rule->error_message = t('You should enter at least two words.');
  $export['title_min_words'] = $rule;

  return $export;
}
