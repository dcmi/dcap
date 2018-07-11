// $Id$
(function ($) {

  Drupal.behaviors.bartik = {
    attach: function(context) {

      $('#search-block-form input[type=text]').val(Drupal.t('Search'));

      $('#search-block-form input[type=text]').focus(function(){
        $(this).addClass('has-focus');
        if ($(this).val() == Drupal.t('Search')) {
          $(this).val('');
        }
      });

      $('#search-block-form input[type=text]').blur(function(){
        $(this).removeClass('has-focus');
        if ($(this).val() == '') {
          $(this).val(Drupal.t('Search'));
        }
      });
    }

  };

})(jQuery);
