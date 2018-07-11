<?php
/**
 * @file
 * Field validation PCRE validator.
 *
 */
$plugin = array(
  'label' => t('Regular expression (Perl-Compatible)'),
  'description' => t('Validates user-entered text against a specified regular expression using the <a href="http://php.net/manual/en/book.pcre.php">PCRE</a> function\'s family.'),
  'handler' => array(
    'class' => 'field_validation_pcre_validator',
  ),
);

class field_validation_pcre_validator extends field_validation_validator {

  /**
   * Validate field.
   */
  public function validate() {
    $pattern = $this->rule->settings['data'];
    if ($this->value != '' && (!preg_match($pattern, $this->value))) {
      $this->set_error();
    }
  }

  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Pattern'),
      '#description' => t("Specify the Perl-compatible regular expression pattern to validate the user input against."),
      '#type' => 'textarea',
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }
}
