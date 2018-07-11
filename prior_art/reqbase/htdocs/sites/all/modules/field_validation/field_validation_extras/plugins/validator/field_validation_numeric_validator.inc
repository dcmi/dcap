<?php
/**
 * @file
 * Field validation numeric validator.
 *
 */
$plugin = array(
  'label' => t('Numeric(HTML5)'),
  'description' => t('Verifies that user-entered values are numeric, with the option to specify min/max/step.'),
  'handler' => array(
    'class' => 'field_validation_numeric_validator',
  ),
);

class field_validation_numeric_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value !== '' && !is_null($this->value)) {
      $flag = TRUE;
      if (!is_numeric($this->value)) {
        $flag = FALSE;
      }
      else{
        if (isset($settings['min']) && $settings['min'] != '') {
          $min = token_replace($settings['min'], array($this->get_token_type() => $this->entity));
		  if ($this->value < $min) {
            $flag = FALSE;
          }
        }
        if (isset($settings['max']) && $settings['max'] != '') {
          $max = token_replace($settings['max'], array($this->get_token_type() => $this->entity));
		  if ($this->value > $max) {
            $flag = FALSE;
          }
        }
        if (isset($settings['step']) && strtolower($settings['step']) != 'any') {
          // Check that the input is an allowed multiple of #step (offset by #min if
          // #min is set).
          $offset = isset($settings['min']) ? $settings['min'] : 0.0;
          $step = token_replace($settings['step'], array($this->get_token_type() => $this->entity));
          //The logic code was copied from Drupal 8 core.
          if ($step > 0 && !$this->valid_number_step($this->value, $step, $offset)) {
           $flag = FALSE;
          }
        }
      }
      if (!$flag) {
        $token = array(
          '[min]' => isset($min) ? $min : '',
          '[max]' => isset($max) ? $max : '',
          '[step]' => isset($step) ? $step : '',
        );
        $this->set_error($token);
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['min'] = array(
      '#title' => t('Minimum value'),
      '#description' => t("Optionally specify the minimum value to validate the user-entered numeric value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum value'),
      '#description' => t("Optionally specify the maximum value to validate the user-entered numeric value against."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['max']) ? $default_settings['max'] : '',
    );
    $form['settings']['step'] = array(
      '#title' => t('Step'),
      '#description' => t("The step scale factor. Must be positive."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['step']) ? $default_settings['step'] : '',
    );
    parent::settings_form($form, $form_state);
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    $token_help = parent::token_help();
    $token_help += array(
      '[min]' => t('Minimum value'), 
      '[max]' => t('Maximum value'),
      '[step]' => t('Step'),
    );
    return $token_help;
  }
  /**
   * Verifies that a number is a multiple of a given step.
   *
   * The implementation assumes it is dealing with IEEE 754 double precision
   * floating point numbers that are used by PHP on most systems.
   *
   * This is based on the number/range verification methods of webkit.
   *
   * @param $value
   *   The value that needs to be checked.
   * @param $step
   *   The step scale factor. Must be positive.
   * @param $offset
   *   (optional) An offset, to which the difference must be a multiple of the
   *   given step.
   *
   * @return bool
   *   TRUE if no step mismatch has occured, or FALSE otherwise.
   *
   * @see http://opensource.apple.com/source/WebCore/WebCore-1298/html/NumberInputType.cpp
   */
  public function valid_number_step($value, $step, $offset = 0.0) {
    $double_value = (double) abs($value - $offset);

    // The fractional part of a double has 53 bits. The greatest number that could
    // be represented with that is 2^53. If the given value is even bigger than
    // $step * 2^53, then dividing by $step will result in a very small remainder.
    // Since that remainder can't even be represented with a single precision
    // float the following computation of the remainder makes no sense and we can
    // safely ignore it instead.
    if ($double_value / pow(2.0, 53) > $step) {
      return TRUE;
    }

    // Now compute that remainder of a division by $step.
    $remainder = (double) abs($double_value - $step * round($double_value / $step));

    // $remainder is a double precision floating point number. Remainders that
    // can't be represented with single precision floats are acceptable. The
    // fractional part of a float has 24 bits. That means remainders smaller than
    // $step * 2^-24 are acceptable.
    $computed_acceptable_error = (double)($step / pow(2.0, 24));

    return $computed_acceptable_error >= $remainder || $remainder >= ($step - $computed_acceptable_error);
  }
}