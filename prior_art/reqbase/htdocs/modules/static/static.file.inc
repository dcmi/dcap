<?php

/**
 * @file
 * The file manipulation functions for the static module.
 *
 * These are all the functions necessary to manipulate the static cache.
 */

/**
 * Copy a file from drupal to static.
 */
function static_copy_files($files) {
  $copy_files = array();
  $wrapper = file_stream_wrapper_get_instance_by_uri('public://');
  $files_dir = $wrapper->getDirectoryPath();

  foreach ($files as $file) {
    // File may be urlencoded.
    $file = urldecode($file);
    // Check if the file needs to be copied over.
    if (static_check_file($file)) {
      // Make sure the destination exists.
      $directory = dirname(static_get_normal_cache_dir() . '/' . $file);
      if (!static_mkdir($directory)) {
        return FALSE;
      }
      // Special case for image styles. We can't directly copy if they haven't
      // been generated yet.
      if (strpos($file, $files_dir . '/styles') === 0 && !file_exists($file)) {
        // Should optimize this for multithreaded gets.
        $absolute_url = urldecode(url($file, array('absolute' => TRUE, 'alias' => TRUE)));
        $request = drupal_http_request($absolute_url);

        if ($request->code == 200) {
          $oldumask = umask(0);
          static_write_file(static_get_normal_cache_dir() . '/' . $file, $request->data, 0644);
          umask($oldumask);
        }
      }
      elseif (substr($file, -strlen('.css')) === '.css') {
        // Process contents of css files for other linked data.
        $contents = static_get_css_file_contents($file);
        static_copy_linked_files($contents, dirname($file));
        static_file_copy_to_cache_dir($file);
      }
      elseif (substr($file, -strlen('.js')) === '.js') {
        // Process contents js files for other linked data.
        $contents = file_get_contents($file);
        static_copy_linked_files($contents, dirname($file));
        static_file_copy_to_cache_dir($file);
      }
      else {
        static_file_copy_to_cache_dir($file);
      }
    }
  }
}

/**
 * Returns a clean file path.
 *
 * @param string $file_path
 *   The file path.
 * @param string $source_dir
 *   Optional. A source directory for resolving relative paths.
 *
 * @return string
 *   The clean file path.
 */
function static_clean_file_path($file_path, $source_dir = NULL) {
  global $base_url;

  // Strip off the querystring.
  $clean = preg_replace('/\?.*/', '', $file_path);

  // If path is relative, add on source base.
  if ($source_dir && strpos($clean, '.') === 0) {
    $clean = $source_dir . '/.' . $clean;
  }

  // Strip leading strings.
  if (stripos($clean, 'http') === 0) {
    // Process urls.
    if (stripos($clean, $base_url . '/') === 0) {
      // Strip base url.
      $clean = str_replace($base_url . '/', '', $clean);
    }
    else {
      // Remote files are not processed.
      return '';
    }
  }
  else {
    // Strip leading "/".
    $clean = ltrim($clean, '/');
  }

  return $clean;
}

/**
 * Copy the source file to the static directory.
 */
function static_file_copy_to_cache_dir($source) {
  $dest = static_get_normal_cache_dir() . '/' . $source;
  $oldumask = umask(0);
  if (@copy($source, $dest)) {
    chmod($dest, 0644);
  }
  umask($oldumask);
}

/**
 * Processes the contents of a css file.
 *
 * @param string $file_path
 *   The css file path.
 *
 * @see drupal_build_css_cache()
 */
function static_get_css_file_contents($file_path) {
  $contents = drupal_load_stylesheet($file_path, TRUE);
  if (empty($contents)) {
    return '';
  }

  // Build the base URL of this CSS file: start with the full URL.
  $css_base_url = file_create_url($file_path);
  // Move to the parent.
  $css_base_url = substr($css_base_url, 0, strrpos($css_base_url, '/'));
  // Simplify to a relative URL if the stylesheet URL starts with the
  // base URL of the website.
  if (substr($css_base_url, 0, strlen($GLOBALS['base_root'])) == $GLOBALS['base_root']) {
    $css_base_url = substr($css_base_url, strlen($GLOBALS['base_root']));
  }

  _drupal_build_css_path(NULL, $css_base_url . '/');
  // Anchor all paths in the CSS with its base URL, ignoring external and absolute paths.
  $contents = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $contents);

  return $contents;
}

/**
 * Check to see if a file needs to be copied.
 */
function static_check_file($file) {
  $static_checked_files = &drupal_static(__FUNCTION__);

  // If it is set. We don't need to check again.
  if (isset($static_checked_files[$file])) {
    return FALSE;
  }

  // Do not copy if the file cannot be read.
  if (!is_readable($file)) {
    return FALSE;
  }

  // If the file doesn't exists, we should try to copy it over.
  if (!file_exists(static_get_normal_cache_dir() . '/' . $file)) {
    return TRUE;
  }

  // Check to see if the file has changed.
  // Note: md5 is slow on larger files. If the sites has many larger files we
  // may need to consider something faster.
  if (md5_file($file) != md5_file(static_get_normal_cache_dir() . '/' . $file)) {
    return TRUE;
  }

  // At this point we know the file exists and is the same as drupal's version.
  $static_checked_files[$file] = TRUE;
  return FALSE;
}

/**
 * Create a redirect page.
 */
function static_redirect_page($oldfile, $newfile) {
  // This is a simple html page that redirects to the new page.
  $data = '<html>' . PHP_EOL
      . '  <head>' . PHP_EOL
      . '    <meta http-equiv="refresh" content="0;URL=/' . $newfile . '">' . PHP_EOL
      . '  </head>' . PHP_EOL
      . '  <body>' . PHP_EOL
      . '    <a href="/' . $newfile . '">Page has moved to this location.</a>' . PHP_EOL
      . '  </body>' . PHP_EOL
      . '</html>' . PHP_EOL;

  // Create directory if it doesn't exist.
  $directory = dirname(static_get_normal_cache_dir() . '/' . $oldfile);
  if (!static_mkdir($directory)) {
    return FALSE;
  }
  // Save the redirect to the system.
  if (file_put_contents(static_get_normal_cache_dir() . '/' . $oldfile, $data) === FALSE) {
    watchdog('static', 'Could not create the file %file on your system', array('%file' => $oldfile), WATCHDOG_ERROR);
    return FALSE;
  }
}

/**
 * Write to a file. Ensures write is atomic via rename operation.
 */
function static_write_file($filename, $data, $chmod = 0644) {
  // Create directory if it doesn't exist.
  $directory = dirname($filename);
  if (!static_mkdir($directory)) {
    return FALSE;
  }

  // If the file exists and the contents match, don't overwrite. This preserves
  // the last modified date.
  if (file_exists($filename) && md5(file_get_contents($filename)) == md5($data)) {
    return TRUE;
  }

  // Save the file to the system.
  if (file_put_contents($filename, $data) === FALSE) {
    watchdog('static', 'Could not create the file %file on your system', array('%file' => $filename), WATCHDOG_ERROR);
    return FALSE;
  }

  // Chmod file so webserver can send it out.
  drupal_chmod($filename, $chmod);
  return TRUE;
}

/**
 * Create a directory.
 */
function static_mkdir($directory) {
  global $_static;

  // Only do something if it's not a dir.
  if (!is_dir($directory)) {
    if (!static_in_cache_dir($directory)) {
      return FALSE;
    }

    // Try to create the directory.
    $oldumask = umask(0);
    $mode = variable_get('file_chmod_directory', 0777);
    if (!mkdir($directory, $mode, TRUE)) {
      watchdog('static', 'Could not create the directory %dir on your system', array('%dir' => $directory), WATCHDOG_ERROR);
      umask($oldumask);
      return FALSE;
    }
    umask($oldumask);
  }
  return TRUE;
}

/**
 * Delete directory and everything under it.
 */
function static_delete_dir($dir) {
  $files = array_diff(scandir($dir), array('.', '..'));
  foreach ($files as $file) {
    if (is_link("$dir/$file") || is_file("$dir/$file")) {
      drupal_unlink("$dir/$file");
    }
    elseif (is_dir("$dir/$file")) {
      static_delete_dir("$dir/$file");
    }
  }
  return drupal_rmdir($dir);
}

/**
 * Returns the relative normal static dir. static/normal.
 */
function static_get_normal_cache_dir() {
  return variable_get('static_root_cache_dir', STATIC_ROOT_CACHE_DIR) . '/' . variable_get('static_normal_dir', STATIC_NORMAL_DIR);
}

/**
 * Verify that the operation is going to operate in the cache dir.
 */
function static_in_cache_dir($file) {
  global $_static;

  $good = TRUE;
  $real_file = realpath($file);
  $cache_dir = variable_get('static_root_cache_dir', STATIC_ROOT_CACHE_DIR);
  $real_cache_dir = realpath($cache_dir);

  // Only operate in the cache dir.
  // Check the real path.
  if (strpos($file, $cache_dir) !== 0
      || ($real_file && $real_cache_dir && strpos($real_file, $real_cache_dir) !== 0)
        ) {
    $good = FALSE;
  }

  // Send error to watchdog.
  if (!$good) {
    watchdog('static', 'An operation outside of the cache directory was attempted on your system. %file or %real_file is outside the cache directory %cache or %real_cache.', array(
      '%file'       => $file,
      '%real_file'  => $real_file,
      '%cache'      => $cache_dir,
      '%real_cache' => $real_cache_dir,
      ),
    WATCHDOG_CRITICAL);
  }

  return $good;
}
