(function ($) {

Drupal.behaviors.fusionHasJS = {
  attach: function (context, settings) {
    $('html').removeClass('no-js');
  }
};

Drupal.behaviors.fusionEqualheights = {
  attach: function (context, settings) {
    if (jQuery().equalHeights) {
      $("#header-top-wrapper div.equal-heights div.content").equalHeights();
      $("#header-group-wrapper div.equal-heights div.content").equalHeights();
      $("#preface-top-wrapper div.equal-heights div.content").equalHeights();
      $("#preface-bottom div.equal-heights div.content").equalHeights();
      $("#sidebar-first div.equal-heights div.content").equalHeights();
      $("#content-region div.equal-heights div.content").equalHeights();
      $("#node-top div.equal-heights div.content").equalHeights();
      $("#node-bottom div.equal-heights div.content").equalHeights();
      $("#sidebar-second div.equal-heights div.content").equalHeights();
      $("#postscript-top div.equal-heights div.content").equalHeights();
      $("#postscript-bottom-wrapper div.equal-heights div.content").equalHeights();
      $("#footer-wrapper div.equal-heights div.content").equalHeights();
    }
  }
};

Drupal.behaviors.fusionIE6fixes = {
  attach: function (context, settings) {
    // IE6 & less-specific functions
    // Add hover class to main menu li elements on hover
    if ($.browser.msie && ($.browser.version < 7)) {
      $('form input.form-submit').hover(function() {
        $(this).addClass('hover');
        }, function() {
          $(this).removeClass('hover');
      });
      $('#search input#search_header').hover(function() {
        $(this).addClass('hover');
        }, function() {
          $(this).removeClass('hover');
      });
    };
  }
};

Drupal.behaviors.fusionOverlabel = {
  attach: function (context, settings) {
    if (jQuery().overlabel) {
      $("div.fusion-horiz-login label").overlabel();
    }
  }
};

})(jQuery);