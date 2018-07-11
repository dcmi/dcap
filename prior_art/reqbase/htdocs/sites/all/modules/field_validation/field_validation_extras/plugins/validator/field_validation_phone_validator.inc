<?php
/**
 * @file
 * Field validation phone validator. The code is ported from phone module.
 *
 */
$plugin = array(
  'label' => t('Phone'),
  'description' => t('Verifies that user-entered values are valid phone number.'),
  'handler' => array(
    'class' => 'field_validation_phone_validator',
  ),
);

class field_validation_phone_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $settings = $this->rule->settings;
    if ($this->value !== '' && !is_null($this->value)) {
      $country_code = isset($settings['country']) ? $settings['country'] : 'cn';
      $country_regex = '';
      $countries = $this->phone_countries();
      $country_regex = isset($countries[$country_code]['regex']) ? $countries[$country_code]['regex'] : '';
      if (!preg_match($country_regex, $this->value)) {
        $this->set_error();
      }
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $countries = $this->phone_countries();
    $country_options = array();
    foreach ($countries as $country_code => $country) {
      $country_options[$country_code] = isset($country['name']) ? $country['name'] : '';
    }

    $form['settings']['country'] = array(
      '#title' => t('Country'),
      '#type' => 'select',
      '#options' => $country_options, 
      '#default_value' => isset($default_settings['country']) ? $default_settings['country'] : 'cn',
    );
    parent::settings_form($form, $form_state);
  }
  
  function phone_countries() {
   $countries = array(
      'fr' => array(
        'name' => t('France'),
        'regex' => '/(\+33|0)([1-9]\d{8}|85\d{7}|87[0-57-9]\d{6})$/',
      ),
      'be' => array(
        'name' => t('Belgium'),
        'regex' => '/^(\+32|0)[1-9]\d{7,8}$/i',
      ),
      'it' => array(
        'name' => t('Italy'),
        'regex' => "/^(\+39)?[ ]?([0-9]{2,3}(\/|-| )?[0-9]{6,7})$/i",
      ),
      'el' => array(
        'name' => t('Greece'),
        'regex' => "/^(\+30)?[ ]?([0-9]{3,4}(\/|-| )?[0-9]{6,7})$/i",
      ),
      'ch' => array(
        'name' => t('Switzerland'),
        'regex' => "%(\+41|0|0041)([2-9]\d{8})$%",
      ),
      'ca' => array(
        'name' => t('US & Canada'),
        'regex' => '/\D*(\d*)\D*[2-9][0-8]\d\D*[2-9]\d{2}\D*\d{4}\D*\d*\D*/x',
      ),
      'cr' => array(
        'name' => t('Costa Rica'),
        'regex' => "/(00)?[\s|-]?((\+)?[\s|-]?[0-9]{3})?[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?([0-9]{2})[\s|-]?/",
      ),
      'pa' => array(
        'name' => t('Panama'),
        'regex' => '/((00|\+)?[0-9]{3}[\s])?([0-9]{3,4})[\s|-]?([0-9]{4})/',
      ),
      'gb' => array(
        'name' => t('Great Britain - United Kingdom'),
        'regex' => "/((^\+44\s?(\(0\))?\d{4}|^\(?0\d{4}\)?){1}\s?\d{3}\s?\d{3}|(^\+44\s?(\(0\))?\d{3}|^\(?0\d{3}\)?){1}\s?\d{3}\s?\d{4}|(^\+44\s?(\(0\))?\d{2}|^\(?0\d{2}\)?){1}\s?\d{4}\s?\d{4}|(^\+44\s?(\(0\))?\d{1}|^\(?0\d{1}\)?){1}\s?\d{5}\s?\d{5})(\s?\#\d*)?/x",
      ),
      'ru' => array(
        'name' => t('Russia'),
        'regex' => "/\D*[78]?\D*\d{3,5}\D*\d{1,3}\D*\d{2}\D*\d{2}\D*/x",
      ),
      /*
      'ua' => array(
        'name' => t('Ukraine'),
        'regex' => '',
      ), */
      'es' => array(
        'name' => t('Spain'),
        'regex' => '/^[0-9]{2,3}-? ?[0-9]{6,7}$/',
      ),
      /*
      'au' => array(
        'name' => t('Australia'),
        'regex' => '',
      ), */
      'cs' => array(
        'name' => t('Czech Republic'),
        'regex' => '/^((?:\+|00)420)? ?(\d{3}) ?(\d{3}) ?(\d{3})$/',
      ),
      'hu' => array(
        'name' => t('Poland - mobiles only'),
        'regex' => "/\D*(?:\+?36|06)?(\d\d?)\D*(\d{3})\D*(\d{3,4})\D*$/x",
      ),
      'pl' => array(
        'name' => t('Poland'),
        'regex' => "/^(\+48\s+)?\d{3}(\s*|\-)\d{3}(\s*|\-)\d{3}$/i",
      ),
      'nl' => array(
        'name' => t('Netherland'),
        'regex' => '/([0]{1}[6]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){7})|([0]{1}[1-9]{1}[0-9]{2}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){5})|([0]{1}[1-9]{1}[0-9]{1}[-\s]+[1-9]{1}[\s]*([0-9]{1}[\s]*){6})/x',
      ),
      'se' => array(
        'name' => t('Sweden'),
        'regex' => "/^(([+]\d{2}[ ][1-9]\d{0,2}[ ])|([0]\d{1,3}[-]))((\d{2}([ ]\d{2}){2})|(\d{3}([ ]\d{3})*([ ]\d{2})+))$/i",
      ),
      'za' => array(
        'name' => t('South Africa'),
        'regex' => '/^((?:\+27|27)|0)[ ]*((\d{2})(-| )?(\d{3})(-| )?(\d{4})|(\d{2})( |-)(\d{7}))$/',
      ),
      /*
      'il' => array(
        'name' => t('Israel'),
        'regex' => '',
      ), */
      /*
      'nz' => array(
        'name' => t('New Zealand'),
        'regex' => '',
      ), */
      'br' => array(
        'name' => t('Brazil'),
        'regex' => "/^(\+|0{2}|)?(55|0|)[ -.]?((\(0?[1-9][0-9]\))|(0?[1-9][0-9]))[ -.]?([1-9][0-9]{2,3})[ -.]?([0-9]{4})$/",
      ),
      'cl' => array(
        'name' => t('Chile'),
        'regex' => "/^((\(\d{3}\) ?)|(\d{3}-)|(\(\d{2}\) ?)|(\d{2}-)|(\(\d{1}\) ?)|(\d{1}-))?\d{3}-(\d{3}|\d{4})$/i",
      ),
      'cn' => array(
        'name' => t('China'),
        'regex' => '/^(\+86|86)?( |-)?([0-9]{11}|([0-9]{3,4}(\-|\.| )[0-9]{3,8})|[0-9]{2}( |\-)[0-9]{4}[ ][0-9]{4}|[0-9]{2}\.[0-9]{2}\.[0-9]{2}\.[0-9]{2}\.[0-9]{2})$/',
      ),
      /*
      'hk' => array(
        'name' => t('Hong-Kong'),
        'regex' => '',
      ), 
      'mo' => array(
        'name' => t('Macao'),
        'regex' => '',
      ),  */
      'ph' => array(
        'name' => t('The Philippines'),
        'regex' => "/((^\+63\s?\(?\d{5}\)?|^\(?\d{5}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}|(^\+63\s?\(?\d{4}\)?|^\(?\d{4}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}|(^\+63\s?\(?\d{3}\)?|^\(?\d{3}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}|(^\+63\s?\(?\d{2}\)?|^\(?\d{2}\)?){1}\s?\d{3}(\S?|\s?)?\d{4}|(^\+63\s?\(?\d{1}\)?|^\(?\d{1}\)?){1}\s?\d{3}(\S?|\s?)?\d{4})(\s?\#\d*)?/x",
      ),
      'sg' => array(
        'name' => t('Singapore'),
        'regex' => '/^(\+65)?\s?[689]\d{7}$/i',
      ),
      'jo' => array(
        'name' => t('Jordan'),
        'regex' => "/(^(\+962|00962|962|0)[-\s]{0,1}[7]{1}[7-9]{1}[0-9]{7}$) | (^(\+962|00962|962|0)[-\s]{0,1}[2-6][-\s]{0,1}[0-9]{7}$)/x",
      ),
      /*
      'eg' => array(
        'name' => t('Egypt'),
        'regex' => '',
      ), */
      'pk' => array(
        'name' => t('Pakistan'),
        'regex' => "/^(\+)?([9]{1}[2]{1})?-? ?(\()?([0]{1})?[1-9]{2,4}(\))?-? ??(\()?[1-9]{4,7}(\))?$/i",
      ),
      'in' => array(
        'name' => t('India'),
        'regex' => "/^((\+*)((0[ -]+)*|(91 )*)(\d{12}+|\d{10}+))|\d{5}([- ]*)\d{6}$/i",
      ),
      'dk' => array(
        'name' => t('Denmark'),
        'regex' => "/^(([+]\d{2}[ ][1-9]\d{0,2}[ ])|([0]\d{1,3}[-]))((\d{2}([ ]\d{2}){2})|(\d{3}([ ]\d{3})*([ ]\d{2})+))$/i",
      ),
    );
  
    return $countries;
  }
}