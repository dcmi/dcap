
Recommended/Required modules:
https://drupal.org/node/27882
https://drupal.org/project/disable_all_forms
https://drupal.org/project/expire
https://drupal.org/project/httprl
https://drupal.org/project/xmlsitemap
https://drupal.org/project/esi

Run the static site under apache so the .htaccess works for the redirects.
Ensure AllowOverrides all is set for the directory.
Ensure mod_include and mod_rewrite are enabled in httpd.conf

Edge Side Includes:
It is recommended to put most universal pieces (blocks) into Edge side includes.
This will allow them to be included on page delivery instead of needing to 
rerender the entire site when one of them changes. Common includes are the
main menu, header and footer menus. Others are page blocks with non-static or
shared content.
Apache: See http://httpd.apache.org/docs/current/howto/ssi.html
