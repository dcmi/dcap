<?php
/**
 * @file
 * Field validation required validator.
 *
 */
$plugin = array(
  'label' => t('Required field'),
  'description' => t('This validator allow you set custom validation error messages on required fields.'),
  'handler' => array(
    'class' => 'field_validation_required_validator',
  ),
);

class field_validation_required_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    //The logic copied from Symfony\Component\Validator\Constraints\NotNullValidator
    if (false === $this->value || (empty($this->value) && '0' != $this->value)) {
      $this->set_error();
    }
  }
}