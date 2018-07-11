<?php
/**
 * @file
 * Bluez theme implementation to display a single Drupal
 * page while offline.
 *
 * All the available variables are mirrored in page.tpl.php. Some may be
 * left blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<div>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</div>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>

<div id="wrap" class="clearfix">

  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <div id="header" class="clearfix" role="banner">
    <div>
      <?php if ($logo): ?>
        <div id="logo">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
        </div>
      <?php endif; ?>
    </div>
  </div>

  <div id="main" role="main" class="clearfix">
    <?php print $messages; ?>
    <a id="main-content"></a>
    <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
    <?php print $content; ?>
  </div> <!-- /#main -->
  
</div> <!-- /#wrapper -->

</body>
</html>
