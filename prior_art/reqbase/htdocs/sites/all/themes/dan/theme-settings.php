<?php

/**
 * @file
 * Theme setting callbacks for the day and night theme.
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function dan_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $form['theme_settings']['toggle_tertiary_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Tertiary menu'),
    '#default_value' => theme_get_setting('toggle_tertiary_menu'),
  );

  $form['tertiary_menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tertiary menu'),
  );

  $form['tertiary_menu']['tertiary_menu'] = array(
    '#type' => 'select',
    '#title' => t('Tertiary menu'),
    '#default_value' => theme_get_setting('tertiary_menu'),
    '#options' => menu_get_menus(),
  );

  return $form;
}
