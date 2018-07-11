<?php
/**
 * @file
 * Property validation unique validator.
 *
 */
$plugin = array(
  'label' => t('Unique values'),
  'description' => t('Verifies that all values are unique in current entity or bundle.'),
  'handler' => array(
    'class' => 'property_validation_unique_validator',
  ),
);

class property_validation_unique_validator extends property_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $flag = TRUE;
    $scope = $this->rule->settings['data'];
    $count = 0;
    if ($flag) {
      $query = new EntityFieldQuery();
      if ($scope == 'entity') {
        $query->entityCondition('entity_type', $this->rule->entity_type);
      }
      elseif ($scope == 'bundle') {
        $query->entityCondition('entity_type', $this->rule->entity_type);
        $query->entityCondition('bundle', $this->rule->bundle);
      }

      list($id, $vid, $bundle) = entity_extract_ids($this->rule->entity_type, $this->entity);
      if ($this->rule->entity_type == 'user' && arg(0) =='user' && arg(2) =='edit' && empty($id)) {
        $id = arg(1);
      }
      if (!empty($id)) {
        $query->entityCondition('entity_id', $id, '!=');
      }
      //Always bypass all access checkings.
      $query->addMetaData('account', user_load(1));
      $count = $query->propertyCondition($this->rule->property_name, $this->value)
        ->count()
        ->execute();
      if ($count) {
        $flag = FALSE;
      }

    }

    if (!$flag) {
      $token = array(
        '[count]' => $count,
      );
      $this->set_error($token);
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Scope of unique'),
      '#description' => t("Specify the scope of unique values, support: entity, bundle."),
      '#type' => 'select',
      '#options' => array(
        'entity' => t('Entity'),
        'bundle' => t('Bundle'),
      ),  
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    $token_help = parent::token_help();
    $token_help += array(
      '[count]' => t('Count of duplicate'),
    );
    return $token_help;
  }
}