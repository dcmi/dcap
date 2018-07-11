/**

 * @file
 * Bluez Slider Javascript.
 *
 */
(function ($) {
  Drupal.behaviors.slider = {
    attach: function (context, settings) {
      $(".paging").show();
      $(".paging a:first").addClass("active");

      // Get size of images.
      var imageWidth = $(".slide-area").width();
      var imageSum = $(".slide_image img").size();
      var imageReelWidth = imageWidth * imageSum;

      // Adjust the Slide image to its new size
      $(".slide_image").css({'width' : imageReelWidth});

      // Paging + Slider Function
      rotate = function(){
        // Get number of times to slide
        var triggerID = $active.attr("rel") - 1;
        var slide_imagePosition = triggerID * imageWidth;

        // Add & Remove active class
        $(".paging a").removeClass('active');
        $active.addClass('active');
        $(".descriptions").stop(true,true).slideUp('fast');
        $(".descriptions").eq($('.paging a.active').attr("rel") - 1).slideDown("fast");
        // Slide Animation
        $(".slide_image").animate({
            left: -slide_imagePosition
        },500);
      };

      // Rotate and Switch
      rotateSwitch = function(){
      $(".descriptions").eq($('.paging a.active').attr("rel") - 1).slideDown("slow");
          play = setInterval(function(){
              $active = $('.paging a.active').next();
              if ($active.length === 0) {
                  $active = $('.paging a:first');
              }
              rotate();
          // Timer speed
          },6000);
      };
      rotateSwitch();
      // Slideshow Pagger
      $(".paging a").click(function() {
         $active = $(this);
         clearInterval(play);
         rotate();
         rotateSwitch();
         return false;
      });
    }
  };
})(jQuery);
