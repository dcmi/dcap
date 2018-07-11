<?php
/**
 * @file
 * Field validation color validator.
 *
 */
$plugin = array(
  'label' => t('Color(HTML5)'),
  'description' => t('Verifies that user-entered value is a valid hexadecimal color value.'),
  'handler' => array(
    'class' => 'field_validation_color_validator',
  ),
);

class field_validation_color_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    if ($this->value !== '' && !is_null($this->value)) {
      //The logic is copied from Drupal 8 core.
      if (!self::validateHex($this->value)) {
        $this->set_error();
      }
    }
  }

  /**
   * Validates whether a hexadecimal color value is syntatically correct.
   *
   * @param $hex
   *   The hexadecimal string to validate. May contain a leading '#'. May use
   *   the shorthand notation (e.g., '123' for '112233').
   *
   * @return bool
   *   TRUE if $hex is valid or FALSE if it is not.
   */
  public static function validateHex($hex) {
    // Must be a string.
    $valid = is_string($hex);
    // Hash prefix is optional.
    $hex = ltrim($hex, '#');
    // Must be either RGB or RRGGBB.
    $length = drupal_strlen($hex);
    $valid = $valid && ($length === 3 || $length === 6);
    // Must be a valid hex value.
    $valid = $valid && ctype_xdigit($hex);
    return $valid;
  }
}