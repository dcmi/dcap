<?php

/**
 * @file
 * Contains theme override functions and preprocess functions for the dan theme.
 */

/**
 * @mainpage
 *
 * Responsive theme based on ZEN.
 *
 * @section id_and_css CSS id and class structure
 *
 * - #page
 *   - #header
 *     - #secondary-menu
 *     - #top
 *       - .region-top-first
 *       - .region-top-second
 *     - #name-and-slogan
 *     - #navigation
 *       - a#logo
 *       - #main-menu
 *   - #breadcrumb
 *   - #main
 *     - #content
 *       - .region-highlighted
 *       - .region-content
 *     - #sidebars
 *       - .region-sidebar-first
 *       - .region-sidebar-second
 *   - #footer
 *     - .region-footer
 *     - #tertiary-menu
 *     - #bottom
 *       - .region-bottom-first
 *       - .region-bottom-second
 *
 * @section colors Colors
 *
 * - lighter-blue: 44BBCC
 * - blue: 009ee1
 * - darker-blue: 045a7f
 * - dark-blue: 006B99
 * - white: fff
 * - lighter-grey: eee
 * - grey: 999
 * - darker-grey: 666
 * - lighter-black: 424242
 * - black: 2c2c2c
 * - darker-black: 343434
 *
 * - red: e6332a
 * - green: 95c11f
 * - yellow: f9b233
 *
 * @section fonts Fonts
 *
 * - arial: Helvetica, Arial,sans-serif
 * - helvetica: Tag-Helvetica-Bold, Arial Black
 * - courier:  Courier, Courier New
 *
 * @section files Files
 *
 * @subsection settings Settings
 *
 * - @link template.php template.php @endlink
 * - @link theme-settings.php theme-settings.php @endlink
 *
 * @subsection templates Templates
 *
 * - @link templates/page.tpl.php page.tpl.php @endlink
 * - @link templates/book-navigation.tpl.php book-navigation.tpl.php @endlink
 */

/**
 * Override breadcrumb theme function.
 *
 * @see theme_breadcrumb()
 *
 * @ingroup themable
 */
function dan_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $tagged_breadcrumb = array();
    foreach ($breadcrumb as $link) {
      $tagged_breadcrumb[] = '<span class="breadcrumb-link">' . $link . '</span>';
    }

    $output .= '<div class="breadcrumb">' . implode('<span class="separator"></span>', $tagged_breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Add addtional informations as CSS classes to a menu item.
 *
 * Add the menu link ID (mlid) and depth count of the level as CSS classes to
 * all menu items.
 *
 * @see theme_menu_link()
 *
 * @ingroup themable
 */
function dan_menu_link(array $variables) {
  $element = $variables['element'];

  $element['#attributes']['class'][] = 'menu-' . $element['#original_link']['mlid'];
  $element['#attributes']['class'][] = 'level-' . $element['#original_link']['depth'];

  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Preprocessor for html.tpl.php template file.
 */
function dan_preprocess_html(&$vars) {

  // Load css files only if module exists and is enabled.
  $module_support = array(
    'caption_filter',
    'comment',
    'dan_polaroid',
    'logintoboggan',
    'print',
    'search',
  );

  foreach ($module_support as $module) {
    _dan_add_css($module);
  }
}

/**
 * Add css files only if module exists and is enbled.
 *
 * @param string $module
 *   Name of the module.
 */
function _dan_add_css($module) {
  $path = drupal_get_path('theme', 'dan') . '/css/module-support/';
    if (module_exists($module)) {
    drupal_add_css($path . 'dan.' . str_replace('_', '-', $module) . '.css');
  }
}

/**
 * Override or insert variables into the page templates.
 *
 * @param array $variables
 *   An array of variables to pass to the theme template.
 * @param string $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function dan_preprocess_page(&$variables, $hook) {
  // Main menu.
  if (theme_get_setting('toggle_main_menu')) {
    $main_menu_tree = menu_tree_all_data('main-menu');
    $variables['main_menu'] = menu_tree_output($main_menu_tree);
  }
  else {
    $variables['main_menu'] = NULL;
  }

  // Tertiary menu.
  if (theme_get_setting('toggle_tertiary_menu')) {
    $tertiary_links = theme_get_setting('tertiary_menu');
    $variables['tertiary_menu'] = menu_navigation_links($tertiary_links);
    $menus = function_exists('menu_get_menus') ? menu_get_menus() : menu_list_system_menus();
    $variables['tertiary_menu_heading'] = $menus[$tertiary_links];
  }
  else {
    $variables['tertiary_menu'] = '';
    $variables['tertiary_menu_heading'] = '';
  }
}

/**
 * Implements hook_css_alter().
 */
function dan_css_alter(&$css) {
  unset(
    $css['modules/book/book.css'],
    $css['modules/system/system.menus.css'],
    $css['modules/system/system.messages.css']
  );
}
