<?php
/**
 * @file
 * Integration with feeds to support unique targets in mappers.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see field_feeds_processor_targets_alter().
 */
function field_validation_feeds_processor_targets_alter(&$targets, $entity_type, $bundle) {
  module_load_include('inc', 'ctools', 'includes/export');
  $rules = ctools_export_load_object('field_validation_rule', 'conditions', array('entity_type' => $entity_type, 'bundle' => $bundle, 'validator' => 'field_validation_unique_validator'));
  foreach ($rules as $rule) {
    if (!empty($rule->disabled)) {
      continue;
    }
    $targets[$rule->field_name]['optional_unique'] = TRUE;
    $targets[$rule->field_name]['unique_callbacks'][] = 'field_validation_feeds_existing_entity_id';
  }
}

/**
 * Callback for Feeds processor unique entity ID.
 *
 * @param FeedsSource $source
 *   The Feed source.
 * @param string $entity_type
 *   Entity type for the entity to be processed.
 * @param string $bundle
 *   Bundle name for the entity to be processed.
 * @param string $target
 *   A string identifying the unique target on the entity.
 * @param array $values
 *   The unique values to be checked.
 *
 * @return int
 *   The existing entity id, or 0 if not found.
 *
 * @see field_validation_feeds_processor_targets_alter()
 * @see FeedsProcessor::existingEntityId()
 */
function field_validation_feeds_existing_entity_id(FeedsSource $source, $entity_type, $bundle, $target, array $values) {
  module_load_include('inc', 'ctools', 'includes/export');
  $unique_rules = ctools_export_load_object('field_validation_rule', 'conditions', array('entity_type' => $entity_type, 'bundle' => $bundle, 'field_name' => $target, 'validator' => 'field_validation_unique_validator'));
  $unique_rule = reset($unique_rules);
  if (!empty($unique_rule)) {
    // Get unique entity ID from unique field value. Note that we are not using
    // field_validation_unique_validator::validate() because we don't want to
    // fire set_error().
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', $entity_type)
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($target, $unique_rule->col, $values)
      // Run the query as user 1.
      ->addMetaData('account', user_load(1))
      ->execute();

    if (isset($result[$entity_type])) {
      return key($result[$entity_type]);
    }
  }
}
