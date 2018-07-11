(function($) {
  Drupal.behaviors.static = {

    messages : {},
    
    attach : function(context) {
      this.addPublish();
    },

    addPublish : function() {
      var that = this;
      if (Drupal.settings.static[0] > 0) {
        var message = Drupal.formatPlural(Drupal.settings.static[0], '(1 update)', '(@count updates)', {'@count':Drupal.settings.static[0]});
      }
      else {
        var message = Drupal.t('(Up to date)');
      }
      $('body').append('<div id="static-generator"><a href="' + Drupal.settings.basePath + 'admin/config/system/static">' + Drupal.t('Publish site') + '</a> ' + message + '</div>');
    }
  }
})(jQuery);
