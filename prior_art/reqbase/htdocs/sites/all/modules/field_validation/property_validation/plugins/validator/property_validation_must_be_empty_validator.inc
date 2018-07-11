<?php
/**
 * @file
 * Property validation must be empty validator.
 *
 */
$plugin = array(
  'label' => t('Must be empty'),
  'description' => t("Verifies that a specified textfield remains empty - Recommended use case: used as an anti-spam measure by hiding the element with CSS."),
  'handler' => array(
    'class' => 'property_validation_must_be_empty_validator',
  ),
);

class property_validation_must_be_empty_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
    if ($this->value != '') {
      $this->set_error();
    }
  }

}