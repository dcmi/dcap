<?php
/**
 * @file
 * Property validation email validator.
 *
 */
$plugin = array(
  'label' => t('Email'),
  'description' => t("Verifies that user-entered data is a valid email address."),
  'handler' => array(
    'class' => 'property_validation_email_validator',
  ),
);

class property_validation_email_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
    if ($this->value != '' && (!valid_email_address($this->value))) {
      $this->set_error();
    }
  }

}