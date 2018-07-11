<?php
/**
 * @file
 * Theme setting callbacks for the bluez theme.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function bluez_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['bluez_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bluez Theme Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs in a page'),
    '#default_value' => theme_get_setting('breadcrumbs', 'bluez'),
    '#description'   => t("Check this option to show breadcrumbs in page. Uncheck to hide."),
  );
  $form['bluez_settings']['slideshow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Front Page Slideshow'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['slideshow']['slideshow_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show slideshow'),
    '#default_value' => theme_get_setting('slideshow_display', 'bluez'),
    '#description'   => t("Check this option to show Slideshow in front page. Uncheck to hide."),
  );
  $form['bluez_settings']['slideshow']['slide'] = array(
    '#markup' => t('You can change the description of each slide in the following Slide Settings.'),
  );
  $form['bluez_settings']['slideshow']['slide1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 1'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['bluez_settings']['slideshow']['slide1']['slide1_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Title'),
    '#default_value' => theme_get_setting('slide1_title', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slide1']['slide1_desc'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide1_desc', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slide2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 2'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['bluez_settings']['slideshow']['slide2']['slide2_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Title'),
    '#default_value' => theme_get_setting('slide2_title', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slide2']['slide2_desc'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide2_desc', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slide3'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 3'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['bluez_settings']['slideshow']['slide3']['slide3_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Title'),
    '#default_value' => theme_get_setting('slide3_title', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slide3']['slide3_desc'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide3_desc', 'bluez'),
  );
  $form['bluez_settings']['slideshow']['slideimage'] = array(
    '#markup' => t('To change the Slide Images, Replace the slide-image-1.jpg, slide-image-2.jpg and slide-image-3.jpg in the images folder of the bluez theme folder.'),
  );
  $form['bluez_settings']['social'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Icon'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['social']['display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Social Icon'),
    '#default_value' => theme_get_setting('display', 'bluez'),
    '#description'   => t("Check this option to show Social Icon. Uncheck to hide."),
  );
  $form['bluez_settings']['social']['twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter URL'),
    '#default_value' => theme_get_setting('twitter', 'bluez'),
    '#description' => t("Enter your Twitter Profile URL. example:: http://www.xyz.com"),
  );
  $form['bluez_settings']['social']['facebook'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook URL'),
    '#default_value' => theme_get_setting('facebook', 'bluez'),
    '#description'   => t("Enter your Facebook Profile URL. example:: http://www.xyz.com"),
  );
  $form['bluez_settings']['social']['linkedin'] = array(
    '#type' => 'textfield',
    '#title' => t('LinkedIn URL'),
    '#default_value' => theme_get_setting('linkedin', 'bluez'),
    '#description'   => t("Enter your LinkedIn Profile URL. example:: http://www.xyz.com"),
  );
  $form['bluez_settings']['Welcome'] = array(
    '#type' => 'fieldset',
    '#title' => t('Welcome Text'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['Welcome']['welcome_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Add Title'),
    '#default_value' => theme_get_setting('welcome_title', 'bluez'),
    '#description'   => t("Enter Title for Welcome text at frontpage."),
  );
  $form['bluez_settings']['Welcome']['welcome_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Add Description'),
    '#default_value' => theme_get_setting('welcome_text', 'bluez'),
    '#description'   => t("Enter Description for Welcome text at frontpage."),
  );
  $form['bluez_settings']['Columns'] = array(
    '#type' => 'fieldset',
    '#title' => t('Columns'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['Columns']['columns_markup'] = array(
    '#markup' => t('Default Promoted Area Images are placed at <b>bluez/images/promoted</b>, User will able to change these images path or image name from column\'s description settings.</br><code>Example : &lt;img src="sites/all/themes/bluez/images/promoted/col1.jpg"&gt;</code></br><b>Image Dimensions :</b></br>For 1 Column = Max Width will be 960px</br>For 2 Column = Max Width will be 467px</br>For 3 Column = Max Width will be 306px</br></br>To keep image on top of the conent use below pattern,<code>&lt;div class="image_wrapper"&gt;&lt;img src="sites/all/themes/bluez/images/promoted/col1.jpg"&gt;&lt;/div&gt;"</code>If IMG is not inside the DIV mentioned above, image and content will be inline.'),
  );
  $form['bluez_settings']['Columns']['colonetitle'] = array(
    '#type' => 'textfield',
    '#title' => t('First Column Title'),
    '#default_value' => theme_get_setting('colonetitle', 'bluez'),
    '#description'   => t("Enter Title for First Column."),
  );
  $form['bluez_settings']['Columns']['colone'] = array(
    '#type' => 'textarea',
    '#title' => t('First Column Description'),
    '#default_value' => theme_get_setting('colone', 'bluez'),
    '#description'   => t("Enter Description for First Column."),
  );
  $form['bluez_settings']['Columns']['coltwotitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Second Column Title'),
    '#default_value' => theme_get_setting('coltwotitle', 'bluez'),
    '#description'   => t("Enter Title for Second Column."),
  );
  $form['bluez_settings']['Columns']['coltwo'] = array(
    '#type' => 'textarea',
    '#title' => t('Second Column Description'),
    '#default_value' => theme_get_setting('coltwo', 'bluez'),
    '#description'   => t("Enter Description for Second Column."),
  );
  $form['bluez_settings']['Columns']['colthreetitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Third Column Title'),
    '#default_value' => theme_get_setting('colthreetitle', 'bluez'),
    '#description'   => t("Enter Title for Third Column."),
  );
  $form['bluez_settings']['Columns']['colthree'] = array(
    '#type' => 'textarea',
    '#title' => t('Third Column Description'),
    '#default_value' => theme_get_setting('colthree', 'bluez'),
    '#description'   => t("Enter Description for Third Column."),
  );
  $form['bluez_settings']['footer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['bluez_settings']['footer']['footer_copyright'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show copyright text in footer'),
    '#default_value' => theme_get_setting('footer_copyright', 'bluez'),
    '#description'   => t("Check this option to show copyright text in footer. Uncheck to hide."),
  );
  $form['bluez_settings']['footer']['footer_developed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show theme developed by in footer'),
    '#default_value' => theme_get_setting('footer_developed', 'bluez'),
    '#description'   => t("Check this option to show design & developed by text in footer. Uncheck to hide."),
  );
  $form['bluez_settings']['footer']['footer_developedby'] = array(
    '#type' => 'textfield',
    '#title' => t('Add name developed by in footer'),
    '#default_value' => theme_get_setting('footer_developedby', 'bluez'),
    '#description'   => t("Add name developed by in footer"),
  );
  $form['bluez_settings']['footer']['footer_developedby_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Add link to developed by in footer'),
    '#default_value' => theme_get_setting('footer_developedby_url', 'bluez'),
    '#description'   => t("Add url developed by in footer. example:: http://www.xyz.com"),
  );
}
