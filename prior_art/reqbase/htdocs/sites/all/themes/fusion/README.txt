WHERE TO START
--------------

Welcome to Fusion! Most of Fusion's documentation lives on the web, but we'll 
give you a quick overview here and point to the most important resources.


INSTALLATION
------------

 1. Download Fusion from http://drupal.org/project/fusion

 2. Unpack the downloaded file, take the folders and place them in your
    Drupal installation under one of the following locations:
      sites/all/themes
        making it available to the default Drupal site and to all Drupal sites
        in a multi-site configuration
      sites/default/themes
        making it available to only the default Drupal site
      sites/example.com/themes
        making it available to only the example.com site if there is a
        sites/example.com/settings.php configuration file

    Note: you will need to create the "themes" folder under "sites/all/"
    or "sites/default/".

 3. Install the Fusion Accelerator module: 
    http://drupal.org/project/fusion_accelerator Fusion Accelerator makes Fusion even more powerful, giving you control over Fusion's 
    layout and style options in Drupal's interface. Download and install 
    this module like usual to get the most out of Fusion.

	* How to install modules: http://drupal.org/node/70151

 4. Follow the instructions below to build your own Fusion subtheme.


FURTHER READING
---------------

Full documentation on using Fusion:
  http://fusiondrupalthemes.com/support/documentation

Full documentation on creating a custom Fusion subtheme:
  http://fusiondrupalthemes.com/support/theme-developers

Drupal theming documentation in the Theme Guide:
  http://drupal.org/theme-guide


BUILD YOUR OWN SUBTHEME
-----------------------

*** IMPORTANT ***

* If you add a new template (.tpl.php) file to your subtheme or modify any lines in your subtheme's .info file, you MUST refresh Drupal's cache by clicking the "Clear all caches" button at admin/config/development/performance.

* Alternately, you can install one of the following modules and use their cache clearing functions: 
    Administration menu module (http://drupal.org/project/admin_menu)
    Devel module (http://drupal.org/project/devel)


The Fusion Core base theme (parent theme) is designed to be easily extended by a subtheme (child theme). You shouldn't modify any of the CSS or PHP files in the fusion_core/ folder; but instead create a subtheme of Fusion. The examples below assume Fusion and your subtheme will be in sites/all/themes/

 1. Copy the fusion_starter or fusion_starter_lite folder and rename it to be 
    your new subtheme. IMPORTANT: Only lowercase letters and underscores should be used for the name of your subtheme.

    For example, copy the sites/all/themes/fusion_starter folder and rename it
    as sites/all/themes/sunshine.

	* Which starter theme to use?
	  For a comparison of features, please visit:
    http://fusiondrupalthemes.com/support/theme-developers/subtheming-quickstart

 2. In your new subtheme folder, rename the .info file to include the name of your new subtheme. Then edit the .info file to update the name and description.

    For example, rename the sunshine/fusion_starter.info file to sunshine/sunshine.info. Edit the sunshine.info file and change "name = Fusion 
    Starter" to "name = My Sunshine Theme" and the description to 
    "description = A Fusion subtheme called Sunshine".

 3. On this line: stylesheets[all][] = css/fusion-starter-style.css, replace       the "fusion-starter" part with your theme's name. Rename the css file in       the css/ folder to match. 

    In our example, you would have a file at css/sunshine-style.css

    Next, visit your site's admin/appearance to set your new theme as the default.

 4. Visit your subtheme's settings page (click "Settings" next to it at 
    admin/appearance) to configure basic options and layout.

	* Learn more about .info file values and setting defaults for these theme
	  settings at: 
	  http://fusiondrupalthemes.com/support/theme-developers/subtheming-quickstart


Optional:

    MODIFYING TEMPLATE FILES:
    If you decide you want to modify any of the .tpl.php template files in the
    fusion_core folder, copy them to your subtheme's folder before making any 
    changes. Then rebuild the theme registry.

    For example, copy fusion_core/page.tpl.php to sunshine/page.tpl.php

