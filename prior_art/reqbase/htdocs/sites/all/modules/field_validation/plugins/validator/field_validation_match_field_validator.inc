<?php
/**
 * @file
 * Field validation match against a field validator.
 *
 */
$plugin = array(
  'label' => t('Match against a field'),
  'description' => t("Validate that user-entered data matches against a field, for example must match user's realname."),
  'handler' => array(
    'class' => 'field_validation_match_field_validator',
  ),
);

class field_validation_match_field_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;

    if ($this->value != '') {
      $flag = TRUE;

      $query = new EntityFieldQuery();
      if (!empty($settings['entity_type'])) {
        $query->entityCondition('entity_type', $settings['entity_type']);
      }
      if (!empty($settings['bundle'])) {
        $query->entityCondition('bundle', $settings['bundle']);
      }
      if (!empty($settings['field_name']) && !empty($settings['column'])) {
        $query->fieldCondition($settings['field_name'], $settings['column'], $this->value);
      }
      //Always bypass all access checkings.
      $query->addMetaData('account', user_load(1));
      $flag = (bool)$query->range(0, 1)->count()->execute();
      if (!empty($settings['reverse'])) {
        $flag = $flag ? FALSE : TRUE;
      }     

      if (!$flag) {
        $this->set_error();
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['entity_type'] = array(
      '#title' => t('Entity type'),
      '#description' => t("Machine name. Entity type of the field that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['entity_type']) ? $default_settings['entity_type'] : '',
    );
    $form['settings']['bundle'] = array(
      '#title' => t('Bundle'),
      '#description' => t("Machine name. Bundle of the field that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['bundle']) ? $default_settings['bundle'] : '',
    );
    $form['settings']['field_name'] = array(
      '#title' => t('Field name'),
      '#description' => t("Machine name. Name of the field that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['field_name']) ? $default_settings['field_name'] : '',
    );
    $form['settings']['column'] = array(
      '#title' => t('Column'),
      '#description' => t("Column of the field that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['column']) ? $default_settings['column'] : '',
    );
    $form['settings']['reverse'] = array(
      '#title' => t('Reverse'),
      '#description' => t("If it is checked, it means must not match the field."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['reverse']) ? $default_settings['reverse'] : FALSE,
    );
    parent::settings_form($form, $form_state);
  }

}