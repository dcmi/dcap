<?php

/**
 * Allow themes to alter the theme-specific settings form.
 *
 * With this hook, themes can alter the theme-specific settings form in any way
 * allowable by Drupal's Forms API, such as adding form elements, changing
 * default values and removing form elements. See the Forms API documentation on
 * api.drupal.org for detailed information.
 *
 * Note that the base theme's form alterations will be run before any sub-theme
 * alterations.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function fusion_core_form_system_theme_settings_alter(&$form, $form_state) {
  global $base_url;

  // Get theme name.
  $theme_name = $GLOBALS['theme_key'];

  // Get default theme settings from .info file.
  $theme_data = list_themes();
  $defaults = ($theme_name && isset($theme_data[$theme_name]->info['settings'])) ? $theme_data[$theme_name]->info['settings'] : array();

  // Calculate sidebar width options.
  $width_options = fusion_core_get_width_options($theme_name);

  // Fusion theme settings container
  $form['tnt_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fusion theme settings'),
    '#description' => t('Use these settings to enhance the appearance and functionality of your Fusion theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => -1,
    '#attached' => array(
      'css' => array(drupal_get_path('theme', 'fusion_core') . '/css/settings-form.fusion-core.css'),
    ),
  );

  // General Settings
  $form['tnt_container']['general_settings'] = array(
    '#type' => 'vertical_tabs',
  );

  // Grid settings
  $form['tnt_container']['general_settings']['theme_grid_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Grid Settings'),
    '#description' => t("These settings control the number of columns that will comprise your grid."),
    '#weight' => -15,
  );


  /**
   * Default layout.  Used for large screens in responsive, and for fluid grids and themes with responsive turned off.
   */
  $form['tnt_container']['general_settings']['theme_responsive_desktop'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout: Desktop'),
    '#description' => t('Only this layout will be used.  For tablet and smartphone layouts, enable the <a href="@accelerator">Fusion Accelerator module</a>.',
      array('@accelerator' =>
        url('http://drupal.org/project/fusion_accelerator',
        array('external' => TRUE))
      )
    ),
    '#weight' => -6,
  );

  // sidebar layout
  $form['tnt_container']['general_settings']['theme_responsive_desktop']['sidebar_layout'] = array(
    '#type'          => 'radios',
    '#title'         => t('Sidebar layout for desktops'),
    '#default_value' => theme_get_setting('sidebar_layout'),
    '#options'       => array(
      'sidebars-split' => t('Split sidebars'),
      'sidebars-both-first' => t('Both sidebars first'),
      'sidebars-both-last' => t('Both sidebars last'),
    ),
    '#attributes' => array('class' => array('clearfix', 'responsive')),
    '#weight'         => -5,
  );

  // sidebar widths
  // @todo - once "adjusted regions" have been removed, add settings for widebar widths to every layout.
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_first_width'] = array(
    '#type'          => 'select',
    '#title'         => t('First sidebar width'),
    '#default_value' => theme_get_setting('sidebar_first_width'),
    '#options'       => $width_options,
    '#weight'        => 5,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_first_width']['#options'][$defaults['sidebar_first_width']] .= t(' (default)');
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_second_width'] = array(
    '#type'          => 'select',
    '#title'         => t('Second sidebar width'),
    '#default_value' => theme_get_setting('sidebar_second_width'),
    '#options'       => $width_options,
    '#weight'        => 6,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['sidebar_second_width']['#options'][$defaults['sidebar_second_width']] .= t(' (default)');

  /**
   * If Fusion Accelerator is unavailable, provide Fusion 1.x style grid options.
   * Toggles are based of FAPI #states, but the description is slightly modified
   * based on module availability.
   */
  if (!module_exists('fusion_accelerator')) {
    $form['tnt_container']['general_settings']['theme_grid_config']['#description'] .= ' ' .
      t('<p>Currently you can choose from either a <strong>fluid grid</strong> that will resize using width percentages,
      or a <strong>fixed grid</strong> that remains the same across all devices and browser sizes.</p><p><strong>Pro tip:</strong> Download and enable
      the <a href="@accelerator">Fusion Accelerator module</a> to support responsive layouts.</p>',
      array('@accelerator' =>
        url('http://drupal.org/project/fusion_accelerator',
        array('external' => TRUE))
        )
      );
  }

  // Generate grid type options based on info files
  $grid_options = array();
  if (isset($defaults['theme_grid_options'])) {
    foreach ($defaults['theme_grid_options'] as $grid_option) {
      $grid_type = (substr($grid_option, 7) == 'fluid') ? t('fluid') : t('fixed');
      $grid_options[$grid_option] = (int)substr($grid_option, 4, 2) . t(' column ') . ' - ' . $grid_type;
    }
  }
  $form['tnt_container']['general_settings']['theme_grid_config']['theme_grid'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select a non-responsive grid layout for your theme'),
    '#default_value' => theme_get_setting('theme_grid'),
    '#options'       => $grid_options,
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['theme_grid']['#options'][$defaults['theme_grid']] .= t(' (default)');
  $form['tnt_container']['general_settings']['theme_grid_config']['theme_grid']['#states'] = array(
    'visible' => array(
      ':input[name=responsive_enabled]' => array('value' => '0')
    ),
  );

  // Fluid grid width
  $form['tnt_container']['general_settings']['theme_grid_config']['fluid_grid_width'] = array(
    '#type'          => 'select',
    '#title'         => t('If using a fluid layout, select the maximum width'),
    '#default_value' => theme_get_setting('fluid_grid_width'),
    '#options'       => array(
      'fluid-100' => t('100%'),
      'fluid-95' => t('95%'),
      'fluid-90' => t('90%'),
      'fluid-85' => t('85%'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_grid_config']['fluid_grid_width']['#options'][$defaults['fluid_grid_width']] .= t(' (default)');
  $form['tnt_container']['general_settings']['theme_grid_config']['fluid_grid_width']['#states'] = array(
    'visible' => array(
      ':input[name="responsive_enabled"]' => array('value' => 0)
    ),
  );

  /**
   * Typography
   */
  $form['tnt_container']['general_settings']['theme_font_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Typography'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font'] = array(
    '#type'          => 'select',
    '#title'         => t('Select a new font family'),
    '#default_value' => theme_get_setting('theme_font'),
    '#options'       => array(
      'none' => t('Theme default'),
      'font-family-sans-serif-sm' => t('Sans serif - smaller (Helvetica Neue, Arial, Helvetica, sans-serif)'),
      'font-family-sans-serif-lg' => t('Sans serif - larger (Verdana, Geneva, Arial, Helvetica, sans-serif)'),
      'font-family-serif-sm' => t('Serif - smaller (Garamond, Perpetua, Nimbus Roman No9 L, Times New Roman, serif)'),
      'font-family-serif-lg' => t('Serif - larger (Baskerville, Georgia, Palatino, Palatino Linotype, Book Antiqua, URW Palladio L, serif)'),
      'font-family-myriad' => t('Myriad (Myriad Pro, Myriad, Trebuchet MS, Arial, Helvetica, sans-serif)'),
      'font-family-lucida' => t('Lucida (Lucida Sans, Lucida Grande, Lucida Sans Unicode, Verdana, Geneva, sans-serif)'),
      'font-family-tahoma' => t('Tahoma (Tahoma, Arial, Verdana, sans-serif)'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font_size'] = array(
    '#type'          => 'select',
    '#title'         => t('Change the base font size'),
    '#description'   => t('Adjusts all text in proportion to your base font size.'),
    '#default_value' => theme_get_setting('theme_font_size'),
    '#options'       => array(
      'font-size-10' => t('10px'),
      'font-size-11' => t('11px'),
      'font-size-12' => t('12px'),
      'font-size-13' => t('13px'),
      'font-size-14' => t('14px'),
      'font-size-15' => t('15px'),
      'font-size-16' => t('16px'),
      'font-size-17' => t('17px'),
      'font-size-18' => t('18px'),
    ),
  );
  $form['tnt_container']['general_settings']['theme_font_config']['theme_font_size']['#options'][$defaults['theme_font_size']] .= t(' (default)');

  // Navigation
  $form['tnt_container']['general_settings']['navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Breadcrumb
  $form['tnt_container']['general_settings']['navigation']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display breadcrumb'),
    '#default_value' => theme_get_setting('breadcrumb_display'),
  );

  // Search Settings
  if (module_exists('search')) {
    $form['tnt_container']['general_settings']['search_container'] = array(
      '#type' => 'fieldset',
      '#title' => t('Search results'),
      '#description' => t('What additional information should be displayed on your search results page?'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_snippet'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display text snippet'),
      '#default_value' => theme_get_setting('search_snippet'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_type'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display content type'),
      '#default_value' => theme_get_setting('search_info_type'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_user'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display author name'),
      '#default_value' => theme_get_setting('search_info_user'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_date'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display posted date'),
      '#default_value' => theme_get_setting('search_info_date'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_comment'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display comment count'),
      '#default_value' => theme_get_setting('search_info_comment'),
    );
    $form['tnt_container']['general_settings']['search_container']['search_results']['search_info_upload'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display attachment count'),
      '#default_value' => theme_get_setting('search_info_upload'),
    );
  }

  // Return theme settings form
  return $form;
}

/**
 * @param (string) $theme
 *    Machine name of fusion theme.
 * @return
 *    Array of sidebar widths options.
 */
function fusion_core_get_width_options($theme) {
  $grid_width = (int)substr(theme_get_setting('theme_grid', $theme), 4, 2);

  $grid_type = substr(theme_get_setting('theme_grid', $theme), 7);
  $width_options = array();
  for ($i = 1; $i <= floor($grid_width / 2); $i++) {
    $grid_units = $i . t(' of @total available units', array('@total'=>$grid_width));
    $width_options[$i] = $grid_units;
  }
  return $width_options;
}