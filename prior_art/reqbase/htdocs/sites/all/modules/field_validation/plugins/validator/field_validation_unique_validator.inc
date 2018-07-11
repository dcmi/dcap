<?php
/**
 * @file
 * Field validation unique validator.
 *
 */
$plugin = array(
  'label' => t('Unique values'),
  'description' => t('Verifies that all values are unique in current entity or bundle.'),
  'handler' => array(
    'class' => 'field_validation_unique_validator',
  ),
);

class field_validation_unique_validator extends field_validation_validator {

  /**
   * Validate field.
   */
  public function validate() {
    $flag = TRUE;
    $scope = $this->rule->settings['data'];
    $count = 0;
    foreach ($this->items as $delta1 => $item1) {
      if ($this->delta != $delta1) {
        if ($this->value == $item1[$this->rule->col]) {
          $flag = FALSE;
          break;
        }
      }
    }
    if ($flag) {
      $query = new EntityFieldQuery();
      if ($scope == 'global') {
      }
      elseif ($scope == 'entity') {
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
      if ($this->rule->entity_type == 'field_collection_item' && arg(0) == 'field-collection' && arg(3) =='edit' && empty($id)) {
        $id = arg(2);
      }
      if ($this->rule->entity_type == 'profile2' && empty($id)) {
        $arg_index = 1;
        if (module_exists('profile2_page')) {
          $profile_type = profile2_type_load($this->entity->type);
          $path = profile2_page_get_base_path($profile_type);
          $arg_index = count(explode('/', $path));
        }
        $uid = arg($arg_index);
        if (arg($arg_index + 1) == 'edit' && is_numeric($uid) && $account = user_load($uid)) {
          if ($profile = profile2_load_by_user($account, $this->entity->type)) {
            $id = $profile->pid;
          }
        }
      }
      if (!empty($id)) {
        $query->entityCondition('entity_id', $id, '!=');
      }
      //Always bypass all access checkings.
      $query->addMetaData('account', user_load(1));
      $query->fieldCondition($this->rule->field_name, $this->rule->col, $this->value);

      // Do the check per user
      if (isset($this->rule->settings['per_user']) && $this->rule->settings['per_user'] && $scope != 'global') {
        global $user;
        $query->propertyCondition('uid', $user->uid);
      }

      // Store a copy of our matched entities for our use in tokens later.
      $matched_entities = $query->execute();

      $count = $query
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

      // Find the first entity that failed this unique condition so we can
      // add a token referencing it. First, we have some special handling for
      // field collection entities so we can find the entity title of
      // whatever the specific field is connected to.
      $entity_types = array_keys($matched_entities);
      $entity_type = reset($entity_types);
      $matched_entity = reset($matched_entities);
      $first_match = reset($matched_entity);
      $entity_info = entity_get_info($entity_type);
      $entity_key_id = $entity_info['entity keys']['id'];
      $entitys = entity_load($entity_type, array($first_match->{$entity_key_id}));
      $entity = reset($entitys);

      if ($entity_type == 'field_collection_item') {
        $host_type = $entity->hostEntityType();
        $host_entity = $entity->hostEntity();
        $label = entity_label($host_type, $host_entity);
        $uri = entity_uri($host_type, $host_entity);
      }
      else {
        $label = entity_label($entity_type, $entity);
        $uri = entity_uri($entity_type, $entity);
      }

      $token['[existing-entity-label]'] = $label;
      $token['[existing-entity-link]'] = l($label, $uri['path'], $uri['options']);

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
      '#description' => t("Specify the scope of unique values, support: global, entity, bundle."),
      '#type' => 'select',
      '#options' => array(
        'global' => t('Global'),
        'entity' => t('Entity Type'),
        'bundle' => t('Bundle'),
      ),
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    $form['settings']['per_user'] = array(
      '#title' => t('Per user'),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['per_user']) ? $default_settings['per_user'] : FALSE,
      '#states' => array(
        'invisible' => array(':input[name="settings[data]"]' => array('value' => 'global')),
      ),
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
      '[existing-entity-label]' => t('The label of the first entity that contains matching data.'),
      '[existing-entity-link]' => t('A link to the first entity that contains matching data.'),
    );
    return $token_help;
  }
}
