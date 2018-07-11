<?php
/**
 * @file
 * Field validation unique values validator.
 *
 */
$plugin = array(
  'label' => t('Unique values on multiple fields'),
  'description' => t('Verifies that all specified fields contain unique values.'),
  'handler' => array(
    'class' => 'field_validation_unique_values_validator',
  ),
);

class field_validation_unique_values_validator extends field_validation_validator {

  /**
   * Validate field.
   */
  public function validate() {
    $flag = FALSE;
    $group_name = $this->rule->settings['data'];
    $field_values = $this->get_field_column_value1($this->items, $this->rule->col);

    foreach ($field_values as $delta => $value) {
      if ($value && $value == $this->value && $delta < $this->delta) {
        $flag = TRUE;
      }
    }

    if (!$flag) {
      ctools_include('export');
      $other_group_rules = ctools_export_load_object('field_validation_rule', 'conditions', array('entity_type' => $this->rule->entity_type, 'bundle' => $this->rule->bundle, 'validator' => $this->rule->validator));

      foreach ($other_group_rules as $other_group_rule) {
        // Skip when do not have the same group name, rule is disabled, equal to current rule.
        if ($other_group_rule->settings['data'] != $group_name || !empty($other_group_rule->disabled) || $other_group_rule->name == $this->rule->name ) {
          continue;
        }

        if (isset($this->entity->{$other_group_rule->field_name}[$this->langcode])) {
          $other_items = $this->entity->{$other_group_rule->field_name}[$this->langcode];
          $other_field_values = $this->get_field_column_value1($other_items, $other_group_rule->col);

          $total_field_values = array_merge($field_values, $other_field_values);
          $duplicate_values = array_unique(
            array_diff_assoc($total_field_values, array_unique($total_field_values))
          );

          if (in_array($this->value, $duplicate_values)) {
            $flag = TRUE;
            break;
          }
        }
      }
    }
    if ($flag) {
      $this->set_error();
    }

    $break = FALSE;
    return $break;
  }

  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Group name'),
      '#description' => t("Specify the group name for those fields, it should be the same across those fields. Validation rules with the same group name work together."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }

  /**
   * helper function to get field values
   */
  function get_field_column_value1($items, $column ='value') {
    $field_values = array();
    foreach ($items as $delta => $item) {
      if (isset($item[$column])) {
        $field_values[] = $item[$column];
      }
    }
    return $field_values;
  }

}
