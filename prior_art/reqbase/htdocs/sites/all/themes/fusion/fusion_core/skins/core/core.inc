<?php

/**
 * Implements hook_fusion_apply_group_PLUGIN_info().
 */
function fusion_core_fusion_apply_group_core_info() {
  $groups['menus'] = array(
    'title' => t('Menus'),
    'description' => t('Menu and navigation styles.'),
  );
  $groups['fusion_layout'] = array(
    'title' => t('Fusion Grid Settings'),
    'description' => t('Align an element to the grid.'),
    'weight' => -15,
  );  

  return $groups;
}

/**
 * Implements hook_fusion_apply_skin_PLUGIN_info().
 */
function fusion_core_fusion_apply_skin_core_info() {

  $skins = array();
  
  $skins['fusion_skins_block_positioning'] = array(
    'title' => t('Block position'),
    'type' => 'select',
    'description' => t('Change the position of this block (default is to float to the left)'),
    'group' => 'layout',
    'theme hooks' => array('block'),
    'default status' => TRUE,
    'options' => array(
      'fusion-right' => array(
        'title' => 'Float block to the right',
        'class' => array('fusion-right'),
      ),
      'fusion-center' => array(
        'title' => 'Position block in the center',
        'class' => array('fusion-center'),
      ),
      'fusion-clear' => array(
        'title' => 'Clear floats (block drops to a new line)',
        'class' => array('fusion-clear'),
      ),      
    ),
  );
  
  $skins['fusion_skins_content_alignment'] = array(
    'title' => t('Content alignment'),
    'description' => t('Default is left aligned content'),
    'type' => 'select',
    'group' => 'layout',
    'default status' => TRUE,
    'options' => array(
      'fusion-right' => array(
        'title' => 'Center align content within its container',
        'class' => array('fusion-center-content'),
      ),
      'fusion-center' => array(
        'title' => 'Right align content within its container',
        'class' => array('fusion-right-content'),
      ),   
    ),
  );  
  
  $skins['fusion_skins_general_styles'] = array(
    'title' => t('General styles'),
    // 'description' => t('These are some generally useful options for blocks'),
    'theme hooks' => array('block'),
    'type' => 'checkboxes',
    'group' => 'general',
    'default status' => TRUE,
    'options' => array(
      'fusion-callout' => array(
        'title' => t('Text: large, bold callout style'),
        'class' => array('fusion-callout'),
      ),
      'fusion-bold-links' => array(
        'title' => t('Links: bold all links'),
        'class' => array('fusion-bold-links'),
      ),
      'fusion-padding' => array(
        'title' => 'Padding: add 30px extra padding inside block',
        'class' => array('fusion-padding'),
      ),
      'fusion-border' => array(
        'title' => 'Border: add 1px border and 10px padding',
        'class' => array('fusion-border'),
      ),
    ),
  );  
  
  $skins['fusion_equal_heights'] = array(
    'title' => t('Equal heights'),
    'description' => t('Make blocks in a region the same height'),
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel'),
    'type' => 'checkboxes',
    'group' => 'layout',
    'default status' => TRUE,
    'attached' => array(
       'js' => array('js/jquery.equalheights.js'), 
    ),
    'options' => array(
      'equal-heights' => array(
        'title' => 'Equal heights: equalize the heights of blocks with this style in the same region',
        'class' => array('equal-heights'),
      ),
    ),
  );    
  
  $skins['fusion_multicol'] = array(
    'title' => t('List columns'),
    'type' => 'select',
    'description' => t('Put items in lists (menus, list views, etc.) in multiple columns'),    
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'views_view'),    
    'group' => 'general',
    'default status' => TRUE,
    'options' => array(
      'fusion-2-col-list' => array(
        'title' => '2-column list/menu (50%/50%)',
        'class' => array('fusion-2-col-list', 'clearfix'),
      ),
      'fusion-3-col-list' => array(
        'title' => '3-column list/menu (33%/33%/33%)',
        'class' => array('fusion-3-col-list', 'clearfix'),      
      )
    ),
  );   
  
  $skins['fusion_menu'] = array(
    'title' => t('Menu Layout'),
    'type' => 'select',
    'description' => t('Different layouts and alignment options for your menus'),    
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel'),    
    'group' => 'menus',
    'default status' => TRUE,
    'options' => array(
      'fusion-inline-menu' => array(
        'title' => 'Single line menu with separators',
        'class' => array('fusion-inline-menu'),
      ),
      'fusion-multicol-menu' => array(
        'title' => t('Multi-column menu with bold headers (set menu items to Expanded)'),
        'class' => array('fusion-multicol-menu', 'clearfix')
      )
    ),
  );  
  
  $skins['fusion_list_styles'] = array(
    'title' => t('List/menu styles'),
    'type' => 'checkboxes',
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel', 'views_view'),    
    'group' => 'menus',
    'default status' => TRUE,
    'options' => array(
      'fusion-list-bottom-border' => array(
        'title' => t('Bottom border (no bullets)'),
        'class' => array('fusion-list-bottom-border'),
      ),
      'fusion-multicol-menu' => array(
        'title' => t('Extra vertical spacing (no bullets)'),
        'class' => array('fusion-list-vertical-spacing')
      )
    ),
  );  
    
  $skins['fusion_float_imagefield'] = array(
    'title' => t('Image floating styles'),
    'type' => 'select',
    'description' => t('These options will float ImageField images in content to the left or right and add margins'),
    'theme hooks' => array('block', 'node', 'views_view'),    
    'group' => 'layout',
    'default status' => TRUE,
    'options' => array(
      'fusion_float_imagefield_left' => array(
        'title' => t('Float ImageField left'),
        'class' => array('fusion-float-imagefield-left'),
      ),
      'fusion_float_imagefield_right' => array(
        'title' => t('Float ImageField right'),
        'class' => array('fusion-float-imagefield-right'),
      ),
    ),
  );   
  
  $skins['fusion_login'] = array(
    'title' => t('User login block styles'),
    'theme hooks' => array('block', 'panels_display', 'panels_pane', 'panels_panel'),
    'group' => 'box',
    'default status' => TRUE,
    'attached' => array(
       'js' => array('js/jquery.overlabel.js'), 
    ),
    'options' => array(
      'fusion_horizontal_login' => array(
        'title' => t('Horizontal: puts user login block on a single line with label overlays (good for Header Top region)'),
        'class' => array('fusion-horiz-login'),
      ),
    ),
  );
  
  // @todo: detect current grid, and add column settings accordingly.
  $skins['fusion_skins_grid16_width'] = array(
    'title' => t('Width (16 column grid)'),
    'description' => t("Change the width of this block. Fluid grid % widths are relative to the parent region's width. Default widths: sidebar blocks default to the sidebar width; in other regions width is divided equally among all blocks."),    
    'type' => 'select',
    'group' => 'fusion_layout',
    'theme hooks' => array('block'),
    'default status' => TRUE,
    'options' => _fusion_skins_grid_options(16, 960),   
  );  
  
  $skins['fusion_skins_grid12_width'] = array(
    'title' => t('Width (12 column grid)'),
    'description' => t("Change the width of this block. Fluid grid % widths are relative to the parent region's width. Default widths: sidebar blocks default to the sidebar width; in other regions width is divided equally among all blocks."),
    'type' => 'select',
    'group' => 'fusion_layout',
    'theme hooks' => array('block'),
    'default status' => TRUE,
    'options' => _fusion_skins_grid_options(12, 960),   
  );     
  
  return $skins;
}

/**
 * Generates fusion_apply options based on Fusion grid parameters.
 * Assists in hook_fusion_apply_skin_PLUGIN_info() implementation.
 * @return array
 */
function _fusion_skins_grid_options($units, $width) {
  $options = array();
  $unit_width = floor($width / $units);
  for ($i = 1; $i <= $units; $i++) {
    $plural = ($i == 1) ? '' : 's';
    $this_width = $i * $unit_width;
    $this_percentage = round($i * (100 / $units), 2);
    $options["grid{$units}-{$i}"] = array(
      'title' => "$i unit{$plural} wide ({$this_width}px/{$this_percentage}%)",
      'class' => "grid{$units}-{$i}"
    );
  }
  return $options;
}
