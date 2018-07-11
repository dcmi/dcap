<?php
/**
 * @file
 * Field validation field collection unique validator.
 *
 */
$plugin = array(
  'label' => t('Field collection unique'),
  'description' => t("Verifies that user-entered values are unique in field collection item's host entity."),
  'handler' => array(
    'class' => 'field_validation_field_collection_unique_validator',
  ),
);

class field_validation_field_collection_unique_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $flag = TRUE;
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
      $count = 0;
      $query = new EntityFieldQuery();
      
      $query->entityCondition('entity_type', 'field_collection_item');
      $query->entityCondition('bundle', $this->entity->field_name);
      //Always bypass all access checkings.
      $query->addMetaData('account', user_load(1));
      if (isset($this->entity->hostEntity)) {
        $hostEntity = $this->entity->hostEntity;
      }
      list($id, $vid, $bundle) = entity_extract_ids($this->rule->entity_type, $this->entity);

      //add field collection item.
      if (arg(0) == 'field-collection' && arg(1) == strtr($bundle, array('_' => '-')) &&  arg(2) == 'add') {
        $hostEntityType = arg(3);
        $hostEntityId = arg(4);
        $result = entity_load($hostEntityType, array($hostEntityId));
        $hostEntity = reset($result);
      }

      //edit field collection item.
      if (arg(0) == 'field-collection' && arg(1) == strtr($bundle, array('_' => '-'))  && arg(3) =='edit' && empty($id)) {
        $id = arg(2);
        $field_collection_item = field_collection_item_load($id);
        $hostEntity = $field_collection_item->hostEntity();
      }

      if (!empty($hostEntity)) {
        $items  = isset($hostEntity->{$this->entity->field_name}[LANGUAGE_NONE]) ? $hostEntity->{$this->entity->field_name}[LANGUAGE_NONE] : array();
        //$ids = field_collection_field_item_to_ids($items);
        $ids = array();
        foreach ($items as $item) {
          if (!empty($item['value']) && $item['value'] != $id) {
            $ids[] = $item['value'];
          }
        }
        $query->entityCondition('entity_id', $ids, 'IN');
        $query->fieldCondition($this->rule->field_name, $this->rule->col, $this->value);
        $count = $query->count()->execute();
      }

      if ($count) {
        $flag = FALSE;
      }

    }

    if (!$flag) {
      $this->set_error();
    }
  }

}