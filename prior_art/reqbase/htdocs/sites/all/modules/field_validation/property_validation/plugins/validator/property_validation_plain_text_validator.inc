<?php
/**
 * @file
 * Property validation plain text validator.
 *
 */
$plugin = array(
  'label' => t('Plain text (disallow tags)'),
  'description' => t("Verifies that user-entered data doesn't contain HTML tags."),
  'handler' => array(
    'class' => 'property_validation_plain_text_validator',
  ),
);

class property_validation_plain_text_validator extends property_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    if ($this->value != '' && (strcmp($this->value, strip_tags($this->value)))) {
      $this->set_error();
    }
  }

}