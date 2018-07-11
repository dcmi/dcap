<?php
/**
 * @file
 * Responsive Green theme implementation to display a single Drupal page.
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
 * - $is_admin: TRUE if the user has permission to main-menu administration pages.
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
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="header_wrapper">
  <header id="header" role="banner">
    <?php if ($logo): ?><div id="logo"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>"/></a></div>
    <?php endif; ?>
    <h1 id="site-title"><div id="site-description"><?php print $site_slogan; ?></div></h1>
      <?php if ($display): ?>
         <div id="socialbar">
            <ul class="social">
            <?php $options['attributes'] = array('target' => '_blank'); ?>
            <?php if ($facebook): ?><li class="fb"><?php print l(t(''), $facebook, $options); ?></li> <?php endif; ?>
            <?php if ($twitter): ?><li class="tw"><?php print l(t(''), $twitter, $options); ?></li> <?php endif; ?>
            <?php if ($linkedin): ?><li class="ln"><?php print l(t(''), $linkedin, $options); ?></li> <?php endif; ?>
            </ul>
          </div>
        <?php endif; ?>
        </div>
      </div>
    <div class="clear"></div>
  </header>
  <div class="menu_wrapper">
      <nav id="main-menu"  role="navigation">
        <a class="nav-toggle" href="#">Navigation</a>
        <div class="menu-navigation-container">
          <?php print drupal_render($main_menu_tree); ?>
        <div class="clear"></div>
      </nav><!-- end main-menu -->
  </div>
</div>
<div id="container">
    <?php if ($is_front): ?>
    <?php if ($sdisplay): ?>
    <div id="home-slider">
      <div class="flexslider-container">
        <div id="single-post-slider" class="flexslider">
          <ul class="slides">
            <li class="slide" style="display:none;"><img src="<?php print $img1;?>"alt="Slide1"/></li>
            <li class="slide" style="display:none;"><img src="<?php print $img2;?>"alt="Slide2"/></li>
            <li class="slide" style="display:none;"><img src="<?php print $img3;?>" alt="Slide3"/></li>
          </ul><!-- /slides -->
        </div><!-- /flexslider -->
      </div>
    </div>
    <?php endif; ?>
    <div class="Slideshow-region"><?php print render($page['slideshow']); ?></div>
    <?php if (!empty($page['top_first'])): $num1 = 1;  endif; ?>
    <?php if (!empty($page['top_second'])): $num2 = 1;  endif; ?>
    <?php if (!empty($page['top_third'])): $num3 = 1;  endif; ?>
    <?php
      $sum = (isset($num1) . isset($num2) . isset($num3));
      $result = strlen($sum);
      if ($result == 1):$value = "one";endif;
      if ($result == 2):$value = "two";endif;
      if ($result == 3):$value = "three";endif;
      ?>
     <?php if ($page['top_first'] || $page['top_second'] || $page['top_third']): ?> 
     <div id="top-area" class="clearfix <?php print $value ?>">
      <?php if ($page['top_first']): ?>
        <div class="column"><?php print render($page['top_first']); ?></div>
        <?php endif; ?>
        <?php if ($page['top_second']): ?>
        <div class="column"><?php print render($page['top_second']); ?></div>
        <?php endif; ?>
        <?php if ($page['top_third']): ?>
        <div class="column"><?php print render($page['top_third']); ?></div>
      <?php endif; ?>
      </div>
    <?php endif; ?>
    <?php endif; ?>
    <div class="content-sidebar-wrap">
    <div id="content">
      <?php if (theme_get_setting('breadcrumbs', 'responsive_green')): ?><div id="breadcrumbs"><?php if ($breadcrumb): print $breadcrumb; endif;?></div><?php endif; ?>
      <section id="post-content" role="main">
        <?php print $messages; ?>
        <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
      </section> <!-- /#main -->
    </div>
    <?php if ($page['sidebar_first']): ?>
      <aside id="sidebar-first" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>
    </div>
    <?php if ($page['sidebar_second']): ?>
      <aside id="sidebar-second" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>
</div>
<div id="footer">
  <div id="footer_wrapper">
  <?php if (!empty($page['footer_first'])): $num01 = 1;  endif; ?>
      <?php if (!empty($page['footer_second'])): $num02 = 1;  endif; ?>
      <?php if (!empty($page['footer_third'])): $num03 = 1;  endif; ?>
      <?php
        $sum1 = (isset($num01) . isset($num02) . isset($num03));
        $result1 = strlen($sum1);
          if ($result1 == 1):$value1 = "one";endif;
          if ($result1 == 2):$value1 = "two";endif;
          if ($result1 == 3):$value1 = "three";endif;
      ?>
    <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third']): ?> 
      <div id="footer-area" class="clearfix <?php print $value1 ?>">
        <?php if ($page['footer_first']): ?>
        <div class="column"><?php print render($page['footer_first']); ?></div>
        <?php endif; ?>
        <?php if ($page['footer_second']): ?>
        <div class="column"><?php print render($page['footer_second']); ?></div>
        <?php endif; ?>
        <?php if ($page['footer_third']): ?>
        <div class="column"><?php print render($page['footer_third']); ?></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="footer_credit">
    <div class="footer_inner_credit">
    <?php if ($page['footer']): ?>
       <div id="foot">
        <?php print render($page['footer']) ?>
      </div>
   <?php endif; ?>
    <div id="copyright">
     <p class="copyright"><?php print t('Copyright'); ?> &copy; <?php echo date("Y"); ?>, <?php print $site_name; ?> </p> <p class="credits"> <?php print t('Designed and developed by'); ?>  <a href="http://about.me/ankithinglajia" target="_blank">Ankit Hinglajia</a></p>
    <div class="clear"></div>
    </div>
  </div>
  </div>
</div>
