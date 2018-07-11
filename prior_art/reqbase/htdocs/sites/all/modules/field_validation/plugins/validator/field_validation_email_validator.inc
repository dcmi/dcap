<?php
/**
 * @file
 * Field validation email validator.
 *
 */
$plugin = array(
  'label' => t('Email'),
  'description' => t("Verifies that user-entered data is a valid email address."),
  'handler' => array(
    'class' => 'field_validation_email_validator',
  ),
);

class field_validation_email_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    if ($this->value != '' && (!valid_email_address($this->value))) {
      $this->set_error();
    }
  }

}