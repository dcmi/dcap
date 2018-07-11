<?php
/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function corporateclean_breadcrumb($variables){
  $breadcrumb = $variables['breadcrumb'];
  $breadcrumb_separator=theme_get_setting('breadcrumb_separator','corporateclean');
  
  $show_breadcrumb_home = theme_get_setting('breadcrumb_home');
  if (!$show_breadcrumb_home) {
  array_shift($breadcrumb);
  }
  
  if (!empty($breadcrumb)) {
    $breadcrumb[] = drupal_get_title();
    return '<div class="breadcrumb">' . implode(' <span class="breadcrumb-separator">' . $breadcrumb_separator . '</span>', $breadcrumb) . '</div>';
  }
}

function corporateclean_page_alter($page) {

	if (theme_get_setting('responsive_meta','corporateclean')):
	$mobileoptimized = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'MobileOptimized',
		'content' =>  'width'
		)
	);

	$handheldfriendly = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'HandheldFriendly',
		'content' =>  'true'
		)
	);

	$viewport = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'viewport',
		'content' =>  'width=device-width, initial-scale=1'
		)
	);
	
	drupal_add_html_head($mobileoptimized, 'MobileOptimized');
	drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
	drupal_add_html_head($viewport, 'viewport');
	endif;
	
}

function corporateclean_preprocess_html(&$variables) {

	if (!theme_get_setting('responsive_respond','corporateclean')):
	drupal_add_css(path_to_theme() . '/css/basic-layout.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(lte IE 8)&(!IEMobile)', '!IE' => FALSE), 'preprocess' => FALSE));
	endif;
	
	drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(lte IE 8)&(!IEMobile)', '!IE' => FALSE), 'preprocess' => FALSE));
}

/**
 * Override or insert variables into the html template.
 */
function corporateclean_process_html(&$vars) {
	// Hook into color.module
	if (module_exists('color')) {
	_color_html_alter($vars);
	}

}

/**
 * Override or insert variables into the page template.
 */
function corporateclean_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
 
}

function corporateclean_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
  
    unset($form['search_block_form']['#title']);
	
    $form['search_block_form']['#title_display'] = 'invisible';
	$form_default = t('Search');
    $form['search_block_form']['#default_value'] = $form_default;
    $form['actions']['submit'] = array('#type' => 'image_button', '#src' => base_path() . path_to_theme() . '/images/search-button.png');

 	$form['search_block_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '{$form_default}';}", 'onfocus' => "if (this.value == '{$form_default}') {this.value = '';}" );
  }
}

/**
 * Add javascript files for jquery slideshow.
 */
if (theme_get_setting('slideshow_js','corporateclean')):

	drupal_add_js(drupal_get_path('theme', 'corporateclean') . '/js/jquery.cycle.all.js');
	
	//Initialize slideshow using theme settings
	$effect=theme_get_setting('slideshow_effect','corporateclean');
	$effect_time=theme_get_setting('slideshow_effect_time','corporateclean')*1000;
	$slideshow_randomize=theme_get_setting('slideshow_randomize','corporateclean');
	$slideshow_wrap=theme_get_setting('slideshow_wrap','corporateclean');
	$slideshow_pause=theme_get_setting('slideshow_pause','corporateclean');
	
	drupal_add_js('jQuery(document).ready(function($) {
	
	$(window).load(function() {
	
		$("#slideshow img").show();
		$("#slideshow").fadeIn("slow");
		$("#slider-controls-wrapper").fadeIn("slow");
	
		$("#slideshow").cycle({
			fx:    "'.$effect.'",
			speed:  "slow",
			timeout: "'.$effect_time.'",
			random: '.$slideshow_randomize.',
			nowrap: '.$slideshow_wrap.',
			pause: '.$slideshow_pause.',
			pager:  "#slider-navigation",
			pagerAnchorBuilder: function(idx, slide) {
				return "#slider-navigation li:eq(" + (idx) + ") a";
			},
			slideResize: true,
			containerResize: false,
			height: "auto",
			fit: 1,
			before: function(){
				$(this).parent().find(".slider-item.current").removeClass("current");
			},
			after: onAfter
		});
	});
	
	function onAfter(curr, next, opts, fwd) {
		var $ht = $(this).height();
		$(this).parent().height($ht);
		$(this).addClass("current");
	}
	
	$(window).load(function() {
		var $ht = $(".slider-item.current").height();
		$("#slideshow").height($ht);
	});
	
	$(window).resize(function() {
		var $ht = $(".slider-item.current").height();
		$("#slideshow").height($ht);
	});
	
	});',
	array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
	);

endif;

?>