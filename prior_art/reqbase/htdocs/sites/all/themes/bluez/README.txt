About Bluez Theme
=================

Bluez is Corporate Look 960px fixed width theme. It covers,

- Simple and clean design
- Fixed width (960px), 2 Column Layout 
- Drupal standards compliant
- CSS based Multi-level drop-down menus
- Custom and configurable JS Slideshow
- Customized templates includes configurable Welcome, Promoted blocks
- Use of Google Web Fonts


Bluez Theme Settings
====================
As per Standard Practices, user need to copy/place theme at
sites/all/themes

Following configuration options are available at theme settings page.
(appearance -> Settings for Bluez theme)

1. Breadcrumb      : On/Off
2. Slideshow       : On/Off, Title, Description, 
                     Image configurations (Front Page only)
3. Social Icon     : On/Off, URL configurations
4. Welcome Text    : On/Off, 
                     Title & Description configuration (Front Page only)
5. Promoted blocks : Title, 
                     Description for three column block (Front Page only)
6. Footer Options  : On/Off Copyrights and Developed By Information

Drop-Down-Menu Support
=====================
To Enable drop-down menu, 
Select "Show as expanded" from menu items's setting


Gallery Support
=====================
Gallery Images are placed at bluez/images/slideshow

Promoted Area Support
=====================
Default Promoted Area Images are placed at bluez/images/promoted,
User will able to change these images path or image name from column's
description settings.
Example : 
<img src="sites/all/themes/bluez/images/promoted/col1.jpg">

Image Dimensions :
For 1 Column = Max Width will be 960px
For 2 Column = Max Width will be 467px
For 3 Column = Max Width will be 306px

To keep image on top of the conent use below pattern,
<div class="image_wrapper">
  <img src="sites/all/themes/bluez/images/promoted/col1.jpg">
</div>

If IMG is not inside the DIV mentioned above, image and content will be 
inline.

Drupal compatibility:
=====================
This theme is compatible with Drupal 7.x

Design & Developed by
============
http://www.about.me/ujval_shah
