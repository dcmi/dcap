<?php
/**
 * @file
 * Property validation date range validator.
 *
 */
$plugin = array(
  'label' => t('Date range'),
  'description' => t("Validates user-entered data against a specified date range."),
  'handler' => array(
    'class' => 'property_validation_date_range_validator',
  ),
);

class property_validation_date_range_validator extends property_validation_validator {

  /**
   * Validate property. 
   */
  public function validate() {
   
    $data = $this->value;
    if ($data != '' ) {
      $flag = FALSE;
      $settings =  $this->rule->settings;
      $cycle = $settings['cycle'];
      // support date, datetime
      if (!is_numeric($data)) {
        $data = strtotime($data);
      }

      $date_str = date("Y-m-d H:i:s", $data);
      if ($cycle =='global') {
        if (!empty($settings['min'])) {
          $settings['min'] = strtotime($settings['min']);
          $settings['min'] = date("Y-m-d H:i:s", $settings['min']);
        }
        if (!empty($settings['max'])) {
          $settings['max'] = strtotime($settings['max']);
          $settings['max'] = date("Y-m-d H:i:s", $settings['max']);
        }
      }
      if ($cycle =='year') {
        $date_str = substr($date_str, 5);
      }
      elseif ($cycle =='month') {
        $date_str = substr($date_str, 8);
      }
      elseif ($cycle =='week') {
        $week_day = date('w', strtotime($date_str));
        $date_str = substr($date_str, 10);
        $date_str = $week_day . $date_str;
      }
      elseif ($cycle =='day') {
        $date_str = substr($date_str, 11);
      }
      elseif ($cycle =='hour') {
        $date_str = substr($date_str, 14);
      }
      elseif ($cycle =='minute') {
        $date_str = substr($date_str, 17);
      }

      if (!empty($settings['min'])  && $date_str < $settings['min']) {
        $flag = TRUE;
      }
      if (!empty($settings['max'])  && $date_str > $settings['max']) {
        $flag = TRUE;
      }

      if (!empty($settings['reverse'])) {
        $flag = $flag ? FALSE : TRUE;
      }

      if ($flag) {
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
    $form['settings']['cycle'] = array(
      '#title' => t('Cycle of date'),
      '#description' => t("Specify the cycle of date, support: global, year, month, week, day, hour, minute."),
      '#type' => 'select',
      '#options' => array(
        'global' => t('Global'),
        'year' => t('Year'),
        'month' => t('Month'),
        'week' => t('Week'),
        'day' => t('Day'),
        'hour' => t('Hour'),
        'minute' => t('Minute'),
      ),  
      '#default_value' => isset($default_settings['cycle']) ? $default_settings['cycle'] : '',
    );
    $form['settings']['min'] = array(
      '#title' => t('Minimum date'),
      '#description' => t("Optionally specify the minimum date."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['min']) ? $default_settings['min'] : '',
    );
    $form['settings']['max'] = array(
      '#title' => t('Maximum date'),
      '#description' => t("Optionally specify the maximum date."),
      '#type' => 'textfield',
      '#default_value' => isset($default_settings['max']) ? $default_settings['max'] : '',
    );
    $form['settings']['help'] = array(
      '#markup' => t('For minimum and maximum time, we only support date format "Y-m-d H:i:s", here is the relation between cycle and minimum/maximum date format:')
      . theme('item_list', array('items' => array(t('global - [Y-m-d H:i:s]'), t('year - [m-d H:i:s]'), t('month - [d H:i:s]'), t('week - [w H:i:s]'), t('day - [H:i:s]'), t('hour - [i:s]'), t('minute - [s]'))))
      . t('If cycle is "global", it support more date formats which could be converted through strtotime(), such as "now", "+1 month", "+1 day".'),
    );
    $form['settings']['reverse'] = array(
      '#title' => t('Reverse'),
      '#description' => t("If it is checked, it means must not match the range."),
      '#type' => 'checkbox',
      '#default_value' => isset($default_settings['reverse']) ? $default_settings['reverse'] : FALSE,
    );
    parent::settings_form($form, $form_state);
  }

}