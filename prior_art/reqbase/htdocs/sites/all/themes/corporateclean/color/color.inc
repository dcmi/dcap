<?php

// Put the logo path into JavaScript for the live preview.
drupal_add_js(array('color' => array('logo' => theme_get_setting('logo', 'corporateclean'))), 'setting');

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'base' => t('Text color'),
    'link' => t('Headings/Link'),
    'headingshadow' => t('Headings shadow'),
	'slogan' => t('Slogan'),
    'headertop' => t('Header top'),
    'headerbottom' => t('Header bottom'),
	'headermenu' => t('Main menu strip'),
	'headermenulink' => t('Main menu link'),
	'headermenuborder' => t('Main menu/Footer menu border'),
	'headermenubghover' => t('Main menu background hover (>=2 level)'),
	'bannertop' => t('Banner top'),
    'bannerbottom' => t('Banner bottom'),
	'bannerborder' => t('Banner border'),
	'contenttop' => t('Content top'),
    'contentbottom' => t('Content bottom'),
    'blockbg' => t('Block background'),
    'blockshadow' => t('Block shadow'),
	'buttontop' => t('Button top'),
	'buttonbottom' => t('Button bottom'),
	'buttontext' => t('Button text'),
	'buttontextshadow' => t('Button text shadow'),
	'buttonboxshadow' => t('Button box shadow'),
	'buttonbghover' => t('Button background hover'),
	'footer' => t('Footer 1'),
	'footerlink' => t('Footer link'),
	'footerbottomtop' => t('Footer 2 top'),
    'footerbottombottom' => t('Footer 2 bottom'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
	    'base' => '#7a7a7a',
        'link' => '#1487d4',
    	'headingshadow' => '#eaf1ea',
        'slogan' => '#d5d5d5',
        'headertop' => '#2f2f2f',
        'headerbottom' => '#1b1a1a',
		'headermenu' => '#222222',
		'headermenulink' => '#ffffff',
		'headermenuborder' => '#353535',
		'headermenubghover' => '#1b1b1b',
		'bannertop' => '#efeeee',
        'bannerbottom' => '#dadada',
		'bannerborder' => '#fcfcfc',
		'contenttop' => '#e8e8e8',
        'contentbottom' => '#efefef',
		'blockbg' => '#fdfdfd',
		'buttontop' => '#0093c5',
		'buttonbottom' => '#0079a2',
		'buttontext' => '#fefefe',
		'buttontextshadow' => '#003547',
		'buttonboxshadow' => '#939da2',
	    'buttonbghover' => '#008ab8',
		'footer' => '#181818',
		'footerlink' => '#e4e4e4',
		'footerbottomtop' => '#262626',
		'footerbottombottom' => '#1a1a1a',
      ),
    ),
	'alignment' => array(
      'title' => t('Alignment'),
      'colors' => array(
	    'base' => '#7a7a7a',
        'link' => '#de6a00',
    	'headingshadow' => '#ffffff',
        'slogan' => '#d5d5d5',
        'headertop' => '#222222',
        'headerbottom' => '#203e42',
		'headermenu' => '#222222',
		'headermenulink' => '#d4fffd',
		'headermenuborder' => '#222222',
		'headermenubghover' => '#203e42',
		'bannertop' => '#efeeee',
        'bannerbottom' => '#dadada',
		'bannerborder' => '#fcfcfc',
		'contenttop' => '#e8e8e8',
        'contentbottom' => '#efefef',
		'blockbg' => '#fdfdfd',
		'buttontop' => '#db9655',
		'buttonbottom' => '#de6a00',
		'buttontext' => '#fefefe',
		'buttontextshadow' => '#222222',
		'buttonboxshadow' => '#999999',
	    'buttonbghover' => '#de6a00',
		'footer' => '#203e42',
		'footerlink' => '#d4fffd',
		'footerbottomtop' => '#203e42',
		'footerbottombottom' => '#222222',
      ),
    ),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'color/colors.css',
  ),

  // Files to copy.
  'copy' => array(
    'logo.png',
  ),

  // Gradient definitions.
  'gradients' => array(
    array(
      // (x, y, width, height).
      'dimension' => array(0, 0, 0, 0),
      // Direction of gradient ('vertical' or 'horizontal').
      'direction' => 'vertical',
      // Keys of colors to use for the gradient.
      'colors' => array('top', 'bottom'),
    ),
  ),

  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_css' => 'color/preview.css',
  'preview_js' => 'color/preview.js',
  'preview_html' => 'color/preview.html',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
