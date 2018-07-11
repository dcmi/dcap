
(function ($) {
  Drupal.color = {
    logoChanged: false,
    callback: function(context, settings, form, farb, height, width) {
		// Change the logo to be the real one.
		if (!this.logoChanged) {
		$('#preview #preview-logo img').attr('src', Drupal.settings.color.logo);
		this.logoChanged = true;
		}
		// Remove the logo if the setting is toggled off. 
		if (Drupal.settings.color.logo == null) {
		$('div').remove('#preview-logo');
		}
		
		// Text preview.
		$('#preview', form).css('color', $('#palette input[name="palette[base]"]', form).val());
		$('#preview a', form).css('color', $('#palette input[name="palette[link]"]', form).val());
		$('#preview-header-menu a', form).css('color', $('#palette input[name="palette[headermenulink]"]', form).val());
		$('#preview-footer a', form).css('color', $('#palette input[name="palette[footerlink]"]', form).val());
		$('#preview-footer-bottom a', form).css('color', $('#palette input[name="palette[footerlink]"]', form).val());
		$('#preview-slogan', form).css('color', $('#palette input[name="palette[slogan]"]', form).val());
		
		// Headings.
		var headingscolor = $('#palette input[name="palette[link]"]', form).val();
		var headingsshadow = $('#palette input[name="palette[headingshadow]"]', form).val();
		
		$('#preview h1', form).attr('style', "color: " + headingscolor + "; text-shadow: 1px 1px 1px " + headingsshadow + ";");
		
		// Header.
		var gradient_headertop = $('#palette input[name="palette[headertop]"]', form).val();
		var gradient_headerbottom = $('#palette input[name="palette[headerbottom]"]', form).val();
		
		$('#preview #preview-header', form).attr('style', "background-color: " + gradient_headertop + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_headertop + "), to(" + gradient_headerbottom + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_headertop + ", " + gradient_headerbottom + ");");
		
		// Header-menu.
		$('#preview-header-menu', form).css('background-color', $('#palette input[name="palette[headermenu]"]', form).val());
		$('#preview-header-menu', form).css('border-top-color', $('#palette input[name="palette[headermenuborder]"]', form).val());
		$('#preview-header-menu', form).css('border-bottom-color', $('#palette input[name="palette[headermenuborder]"]', form).val());
		
		// Banner.
		var gradient_bannertop = $('#palette input[name="palette[bannertop]"]', form).val();
		var gradient_bannerbottom = $('#palette input[name="palette[bannerbottom]"]', form).val();
		var bannerborder = $('#palette input[name="palette[bannerborder]"]', form).val();
		
		$('#preview #preview-banner', form).attr('style', "background-color: " + gradient_bannertop + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_bannertop + "), to(" + gradient_bannerbottom + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_bannertop + ", " + gradient_bannerbottom + "); border-bottom: 1px solid " + bannerborder + ";");
		
		// Content.
		var gradient_contenttop = $('#palette input[name="palette[contenttop]"]', form).val();
		var gradient_contentbottom = $('#palette input[name="palette[contentbottom]"]', form).val();
		
		$('#preview #preview-content', form).attr('style', "background-color: " + gradient_contenttop + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_contenttop + "), to(" + gradient_contentbottom + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_contenttop + ", " + gradient_contentbottom + ");");
		
		// Block.
		var blockbg = $('#palette input[name="palette[blockbg]"]', form).val();
		$('#preview .block', form).attr('style', "background-color: " + blockbg + ";");
		
		// Footer.
		var gradient_footer = $('#palette input[name="palette[footer]"]', form).val();
		$('#preview #preview-footer', form).attr('style', "background-color: " + gradient_footer + ";");
		
		// Footer bottom.
		var gradient_footerbottomtop = $('#palette input[name="palette[footerbottomtop]"]', form).val();
		var gradient_footerbottombottom = $('#palette input[name="palette[footerbottombottom]"]', form).val();
		
		$('#preview-footer-bottom', form).attr('style', "background-color: " + gradient_footerbottomtop + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_footerbottomtop + "), to(" + gradient_footerbottombottom + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_footerbottomtop + ", " + gradient_footerbottombottom + ");");
		$('#preview-footer-bottom', form).css('border-top-color', $('#palette input[name="palette[headermenuborder]"]', form).val());
		
		// Button.
		var gradient_buttontop = $('#palette input[name="palette[buttontop]"]', form).val();
		var gradient_buttonbottom = $('#palette input[name="palette[buttonbottom]"]', form).val();
		var buttontext = $('#palette input[name="palette[buttontext]"]', form).val();
		var buttontextshadow = $('#palette input[name="palette[buttontextshadow]"]', form).val();
		var buttonboxshadow = $('#palette input[name="palette[buttonboxshadow]"]', form).val();
		
		$('#preview a.more', form).attr('style', "background-color: " + gradient_buttontop + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_buttontop + "), to(" + gradient_buttonbottom + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_buttontop + ", " + gradient_buttonbottom + "); -webkit-box-shadow: 0px 1px 2px " + buttonboxshadow + "; -moz-box-shadow: 0px 1px 2px " + buttonboxshadow + "; box-shadow: 0px 1px 2px " + buttonboxshadow + "; text-shadow: 0 1px 1px " + buttontextshadow + "; color: " + buttontext + ";");

    }
  };
})(jQuery);