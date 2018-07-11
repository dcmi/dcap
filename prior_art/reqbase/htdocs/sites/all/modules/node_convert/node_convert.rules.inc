<?php

/**
 * @file
 * rules integration for the node_convert module
 */

/**
 * Implements hook_rules_event_info().
 * @ingroup rules
 */

function node_convert_rules_event_info() {
  return array(
    'node_convert_converted_node' => array(
      'label' => t('Content has been converted'),
      'module' => 'node',
      'group' => t('Node'),
      'variables' => array(
        'node' => array('type' => 'node', 'label' => t('Converted node')),
      ),
    ),
  );
}
