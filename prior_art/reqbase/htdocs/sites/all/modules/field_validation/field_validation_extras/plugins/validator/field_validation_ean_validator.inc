<?php
/**
 * @file
 * Field validation ean validator.
 *
 */
$plugin = array(
  'label' => t('EAN'),
  'description' => t('Verifies that user-entered values are valid ean number.'),
  'handler' => array(
    'class' => 'field_validation_ean_validator',
  ),
);

class field_validation_ean_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value !== '' && !is_null($this->value)) {
      $val = $this->value;
      if (drupal_strlen($val) > 13) {  
        $this->set_error();     
      }
      else {
        if (drupal_strlen($val) < 13) {
         $val = str_repeat('0', drupal_strlen($val) - 13) + $val;
        }
        if (!($this->attiks_ean13_valid($val))) {  
          $this->set_error();
        }  
      }
    }
  }

  /**
   * EAN validate helper function. The code way copied from http://drupal.org/node/1066936, wrote by attiks(http://drupal.org/user/105002).
   */
  function attiks_ean13_valid($digits) {  
    $even = $digits[1] + $digits[3] + $digits[5] + $digits[7] + $digits[9] + $digits[11];  
    $even = $even * 3;  
    $odd = $digits[0] + $digits[2] + $digits[4] + $digits[6] + $digits[8] + $digits[10];  
    $total = $even + $odd;
    $checksum = $total % 10;  
    if ($checksum != 0) {    
      $checksum = 10 - $checksum;  
    }    
    return $digits[12] == $checksum;
  }  

}