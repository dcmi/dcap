<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 */

/**
 * Implements hook_html_head_alter().
 */
function bluez_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );
}

/**
 * Insert themed breadcrumb page navigation at top of the node content.
 */
function bluez_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Use CSS to hide titile .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    // Comment below line to hide current page to breadcrumb.
    $breadcrumb[] = drupal_get_title();
    $output .= '<div class="breadcrumb">' . implode(' » ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Add javascript files for front-page jquery slideshow.
 */
if (drupal_is_front_page()) {
  drupal_add_js(drupal_get_path('theme', 'bluez') . '/js/slider.js');
}

/**
 * Add Google Fonts.
 */
function bluez_preprocess_html(&$variables) {
  drupal_add_css('http://fonts.googleapis.com/css?family=Open+Sans', array('type' => 'external'));
}

/**
 * Override or insert variables into the page template.
 */
function bluez_preprocess_page(&$vars) {
  $vars['twitter'] = theme_get_setting('twitter', 'bluez');
  $vars['facebook'] = theme_get_setting('facebook', 'bluez');
  $vars['linkedin'] = theme_get_setting('linkedin', 'bluez');
  $vars['theme_path_social'] = base_path() . drupal_get_path('theme', 'bluez');
  $vars['display'] = theme_get_setting('display', 'bluez');
  $vars['footer_copyright'] = theme_get_setting('footer_copyright');
  $vars['footer_developed'] = theme_get_setting('footer_developed');
  $vars['footer_developedby_url'] = filter_xss_admin(theme_get_setting('footer_developedby_url', 'bluez'));
  $vars['footer_developedby'] = filter_xss_admin(theme_get_setting('footer_developedby', 'bluez'));
  $vars['searchblock'] = module_invoke('search', 'block_view', 'form');
  if (module_exists('i18n_menu')) {
    $vars['main_menu_tree'] = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
  }
  else {
    $vars['main_menu_tree'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
  }
  // Frontpage variables.
  $vars['slideshow_display'] = theme_get_setting('slideshow_display', 'bluez');
  $vars['slide1_title'] = theme_get_setting('slide1_title', 'bluez');
  $vars['slide2_title'] = theme_get_setting('slide2_title', 'bluez');
  $vars['slide3_title'] = theme_get_setting('slide3_title', 'bluez');
  $vars['slide1_desc'] = theme_get_setting('slide1_desc', 'bluez');
  $vars['slide2_desc'] = theme_get_setting('slide2_desc', 'bluez');
  $vars['slide3_desc'] = theme_get_setting('slide3_desc', 'bluez');
  $vars['wtitle'] = filter_xss_admin(theme_get_setting('welcome_title', 'bluez'));
  $vars['wtext'] = filter_xss_admin(theme_get_setting('welcome_text', 'bluez'));
  $vars['col1'] = filter_xss_admin(theme_get_setting('colone', 'bluez'));
  $vars['col1title'] = filter_xss_admin(theme_get_setting('colonetitle', 'bluez'));
  $vars['col2'] = filter_xss_admin(theme_get_setting('coltwo', 'bluez'));
  $vars['col2title'] = filter_xss_admin(theme_get_setting('coltwotitle', 'bluez'));
  $vars['col3'] = filter_xss_admin(theme_get_setting('colthree', 'bluez'));
  $vars['col3title'] = filter_xss_admin(theme_get_setting('colthreetitle', 'bluez'));
  $vars['img1'] = base_path() . drupal_get_path('theme', 'bluez') . '/images/slideshow/slide-image-1.jpg';
  $vars['img2'] = base_path() . drupal_get_path('theme', 'bluez') . '/images/slideshow/slide-image-2.jpg';
  $vars['img3'] = base_path() . drupal_get_path('theme', 'bluez') . '/images/slideshow/slide-image-3.jpg';
  $image1var = array(
    'path' => $vars['img1'],
    'alt' => $vars['slide1_title'],
    'title' => $vars['slide1_title'],
    'attributes' => array('class' => 'slide-img'),
  );
  $vars['slideimage1'] = theme('image', $image1var);
  $image2var = array(
    'path' => $vars['img2'],
    'alt' => $vars['slide2_title'],
    'title' => $vars['slide2_title'],
    'attributes' => array('class' => 'slide-img'),
  );
  $vars['slideimage2'] = theme('image', $image2var);
  $image3var = array(
    'path' => $vars['img3'],
    'alt' => $vars['slide3_title'],
    'title' => $vars['slide3_title'],
    'attributes' => array('class' => 'slide-img'),
  );
  $vars['slideimage3'] = theme('image', $image3var);
}
