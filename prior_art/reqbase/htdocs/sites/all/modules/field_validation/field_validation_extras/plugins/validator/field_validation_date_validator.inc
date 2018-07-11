<?php
/**
 * @file
 * Field validation date validator.
 *
 */
$plugin = array(
  'label' => t('Date(ISO)'),
  'description' => t('Verifies that user-entered values are valid date(ISO).'),
  'handler' => array(
    'class' => 'field_validation_date_validator',
  ),
);

class field_validation_date_validator extends field_validation_validator {
  const PATTERN = '/^(\d{4})-(\d{2})-(\d{2})$/';
  
  /**
   * Validate field. 
   */
  public function validate() {
    //The logic copied from Symfony\Component\Validator\Constraints\DateValidator
    if ($this->value !== '' && !is_null($this->value)) {
      if (!preg_match(self::PATTERN, $this->value, $matches) || !checkdate($matches[2], $matches[3], $matches[1])) {
        $this->set_error();
      }
    }
  }
}