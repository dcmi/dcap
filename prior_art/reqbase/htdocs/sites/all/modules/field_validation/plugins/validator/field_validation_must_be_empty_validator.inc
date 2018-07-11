<?php
/**
 * @file
 * Field validation must be empty validator.
 *
 */
$plugin = array(
  'label' => t('Must be empty'),
  'description' => t("Verifies that a specified textfield remains empty - Recommended use case: used as an anti-spam measure by hiding the element with CSS."),
  'handler' => array(
    'class' => 'field_validation_must_be_empty_validator',
  ),
);

class field_validation_must_be_empty_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    if ($this->value != '') {
      $this->set_error();
    }
  }

}