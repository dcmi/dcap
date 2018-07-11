<?php
/**
 * @file
 * Bluez theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['header']: Items for Header Regions (Inner Pages Only).
 * - $page['content_top']: Items for Content Top Regions (Inner Pages Only).
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar (Right Side Only).
 * - $page['bottom']: Items for the Bottom region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>


<div id="wrapper">
  <!-- socialbar Starts -->
  <?php if ($display): ?>
    <div id="socialbar">
      <ul class="social">
        <?php $options['attributes'] = array('target' => '_blank'); ?>
        <?php if ($facebook): ?><li class="fb"><?php print l(t('facebook'), $facebook, $options); ?></li> <?php endif; ?>
        <?php if ($twitter): ?><li class="tw"><?php print l(t('twitter'), $twitter, $options); ?></li> <?php endif; ?>
        <?php if ($linkedin): ?><li class="ln"><?php print l(t('linkedin'), $linkedin, $options); ?></li> <?php endif; ?>
      </ul>
    </div>
  <?php endif; ?>
  <!-- socialbar Ends -->
    
  <!-- Header Starts -->
  <div id="header" class="clearfix">
    <?php if ($logo || $site_slogan): ?>
      <div id="logo_slogan_wrapper">
        <!-- logo START -->
        <?php if ($logo): ?>
          <div id="logo">
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
          </div>
        <?php endif; ?>
        <!-- logo Ends -->
        
        <!-- site slogan Starts -->
        <?php if ($site_slogan): ?>
          <div id="sitename">
            <p><?php print $site_slogan; ?></p><!--site slogan-->
          </div>
        <?php endif; ?>
        <!-- site slogan Ends -->
      </div>
    <?php endif; ?>

    <!-- navigation START -->
    <div id="navigation" class="clearfix">
      <div id="main-menu">
        <?php print drupal_render($main_menu_tree); ?>
      </div>
    </div>
    <!-- navigation Ends -->
  </div>
  <!-- Header Ends -->
  
  <div id="divider_wrapper"><div id="divider"></div></div>
 
  <!-- Header Starts -->
  <?php if ($page['header']): ?>
    <div id="header_wrapper">
      <?php print render($page['header']); ?>
    </div>
  <?php endif; ?>
  <!-- Header Ends -->
  
  <div id="extra">
    <?php if (theme_get_setting('breadcrumbs')): ?><div id="breadcrumbs"><?php if ($breadcrumb): print $breadcrumb; endif;?></div><?php endif; ?>
    <?php print $messages; ?>
  </div>
  <div class="clear"></div>
  
  <div id="main">
    <div id="post-content">
      <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper clearfix"><?php print render($tabs); ?></div><?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
      <?php print render($page['content']); ?>
    </div> <!-- /#main -->
    <?php if ($page['sidebar_first']): ?>
      <div id="sidebar" class="sidebar clearfix">
        <?php print render($page['sidebar_first']); ?>
      </div>  <!-- /#sidebar-first -->
    <?php endif; ?>
  </div>
  <div class="clear"></div>
  
  <!--Footer context Start -->
  <div id="footer-context">
    <!--Footer Start -->
    <div id="footer-bottom">
      <?php print render($page['footer']) ?>
      <?php if ($footer_copyright || $footer_developed): ?>
        <div id="copyright">
        <?php if ($footer_copyright): ?>
          <?php print t('Copyright'); ?> &copy; <?php print date("Y"); ?>, <?php print $site_name; ?>.
        <?php endif; ?>
        <?php if ($footer_developed): ?>
          <span class="developed"><?php print t('Designed & Develop by'); ?>
            <a href="<?php print ($footer_developedby_url); ?> " target="_blank">
              <?php print ($footer_developedby); ?>
            </a>
          </span>
        <?php endif; ?>
        </div>
      <?php endif; ?>
    </div>
    <!--Footer Ends -->
  </div>
  <!--Footer context Ends -->
  <div class="clear"></div>
</div>
