<?php
/**
 * @file
 * Field validation equal values validator.
 *
 */
$plugin = array(
  'label' => t('Equal values on multiple fields'),
  'description' => t('Verifies that all specified fields contain equal values.'),
  'handler' => array(
    'class' => 'field_validation_equal_values_validator',
  ),
);

class field_validation_equal_values_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $flag = FALSE;
    $group_name = $this->rule->settings['data'];

    ctools_include('export');
    $other_group_rules = ctools_export_load_object('field_validation_rule', 'conditions', array('entity_type' => $this->rule->entity_type, 'bundle' => $this->rule->bundle, 'validator' => $this->rule->validator));

    foreach ($this->items as $delta => $item) {
      foreach ($other_group_rules as $other_group_rule) {
        // Skip when do not have the same group name, rule is disabled, equal to current rule.
        if ($other_group_rule->settings['data'] != $group_name || !empty($other_group_rule->disabled) || $other_group_rule->name == $this->rule->name ) {
          continue;
        }

        if (isset($this->entity->{$other_group_rule->field_name}[$this->langcode][$delta])) {
          if ($item[$this->rule->col] == $this->entity->{$other_group_rule->field_name}[$this->langcode][$delta][$other_group_rule->col]) {
          }
          else{
            $flag = TRUE;
            break;
          }
        }
        else{
          $flag = TRUE;
          break;
        }
      }
      if ($flag) {
        break;
      }
    }
    if ($flag) {
      $this->set_error();
    } 

    $break = TRUE;
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

}