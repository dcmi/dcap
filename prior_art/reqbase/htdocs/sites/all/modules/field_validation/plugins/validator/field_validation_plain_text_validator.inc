<?php
/**
 * @file
 * Field validation plain text validator.
 *
 */
$plugin = array(
  'label' => t('Plain text (disallow tags)'),
  'description' => t("Verifies that user-entered data doesn't contain HTML tags."),
  'handler' => array(
    'class' => 'field_validation_plain_text_validator',
  ),
);

class field_validation_plain_text_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    if ($this->value != '' && (strcmp($this->value, strip_tags($this->value)))) {
      $this->set_error();
    }
  }

}