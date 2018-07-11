<?php
/**
 * @file
 * Field validation match against a property validator.
 *
 */
$plugin = array(
  'label' => t('Match against a property'),
  'description' => t("Validate that user-entered data matches against a property, for example must match user's name."),
  'handler' => array(
    'class' => 'field_validation_match_property_validator',
  ),
);

class field_validation_match_property_validator extends field_validation_validator {

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
      if (!empty($settings['property'])) {
        $query->propertyCondition($settings['property'], $this->value);
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
      '#description' => t("Machine name. Entity type of the property that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['entity_type']) ? $default_settings['entity_type'] : '',
    );
    $form['settings']['bundle'] = array(
      '#title' => t('Bundle'),
      '#description' => t("Machine name. Bundle of the property that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['bundle']) ? $default_settings['bundle'] : '',
    );
    $form['settings']['property'] = array(
      '#title' => t('Property'),
      '#description' => t("Name of the property that to be matched against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['property']) ? $default_settings['property'] : '',
    );
    $form['settings']['reverse'] = array(
      '#title' => t('Reverse'),
      '#description' => t("If it is checked, it means must not match the property."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['reverse']) ? $default_settings['reverse'] : FALSE,
    );
    parent::settings_form($form, $form_state);
  }

}