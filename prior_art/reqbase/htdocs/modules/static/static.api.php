<?php

/**
 * Main function to tell the static module to track a path or paths.
 *
 * The is useful for path discovery modules.
 */
static_track_paths($array_paths);

/**
 * Function to tell the static module to regenerate a path.
 *
 * This does not happen immediately. It marks it for regeneration which will
 * happen the next time the process is run. The file is not deleted while
 * waiting for regeneration.
 */
static_set_expired($path);

/**
 * This is called when clicking "Queue all items for regeneration."
 *
 * It is asking for all known paths on the system to register at once.
 *
 * @TODO: For larger sites this might run into resource limits.
 *
 * @return array
 */
function hook_static_refresh_paths() {
  return array(
    'path',
    'node/1',
  );
}

/**
 * Allows altering the paths before they are tracked.
 *
 * @param $paths
 */
function hook_static_refresh_paths_alter(&$paths) {

}

/**
 * Respond to deleting of multiple items.

 * @param $items
 */
function hook_static_delete_multiple($items) {

}

/**
 * Respond to items being marked for regeneration.
 *
 * @param $items
 */
function hook_static_expire_multiple($items) {

}

/**
 * Respond to a file being written to disk.
 *
 * @param $filename
 * @param $data
 */
function hook_static_file($filename, $data) {

}

/**
 * During the processing of a file, check it for additional assets.
 *
 * This is useful for searching the data for files or assets that should
 * also be included with static_track_path().
 *
 * @param $data
 * @param $source_dir
 */
function hook_static_process($data, $source_dir) {

}

/**
 * Alter information about a page.
 *
 * @param $info
 */
function hook_static_info_alter(&$info) {

}

/**
 * After a page has been requested from the server, use this hook to do any
 * alterations that are needed before processing of the page.
 *
 * @param $info
 * @param $request
 */
function hook_static_response_alter(&$info, &$request) {

}

/**
 * Make alterations to the filename of any statically generated file.
 *
 * @param $filename
 * @param $info
 */
function hook_static_filename_alter(&$filename, $info) {

}

/**
 * Add additional statuses to the list on the admin pages.
 *
 * @param $statuses
 */
function hook_statuses_alter(&$statuses) {

}
