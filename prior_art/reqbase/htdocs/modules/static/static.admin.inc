<?php

/**
 * @file
 * Admin page callbacks for the static module.
 */

/**
 * Form builder; Configure static settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function static_admin_settings() {
  $form['static_prod_site'] = array(
    '#type' => 'textfield',
    '#title' => t('Production host'),
    '#weight' => -10,
    '#description' => t('Enter the production url with the protocol (http://) but without a trailing slash. This is used for RSS feeds and can be used for other uses.'),
    '#default_value' => variable_get('static_prod_site', $GLOBALS['base_url']),
  );

  $form['static_root_cache_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Root cache directory'),
    '#default_value' => variable_get('static_root_cache_dir', STATIC_ROOT_CACHE_DIR),
  );

  $form['static_normal_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Normal cache directory'),
    '#default_value' => variable_get('static_normal_dir', STATIC_NORMAL_DIR),
  );

  $form['static_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the cron static generator'),
    '#default_value' => variable_get('static_cron', TRUE),
    '#description'   => t("Use cron to generate static pages on the site."),
  );

  $form['static_button'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the publish button'),
    '#default_value' => variable_get('static_button', TRUE),
    '#description'   => t("Set the publish button for administrators on the site."),
  );

  $form['static_queue_seconds'] = array(
    '#type' => 'textfield',
    '#title' => t('Time (in seconds) to use for generating static pages on every cron run'),
    '#default_value' => variable_get('static_queue_seconds', 30),
    '#description'   => t("If this it too long, it may cause problems with other tasks that run during the cron runs."),
  );

  $form['static_batch_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of items per batch run'),
    '#default_value' => variable_get('static_batch_size', STATIC_DEFAULT_CRON_LIMIT),
    '#size' => 4,
    '#description'   => t("This is the number of items to process per batch run. If too large, it may cause timeout issues."),
  );

  return system_settings_form($form);
}

/**
 * Page callback for static status.
 */
function static_admin_status() {
  $total = 0;

  $statuses = static_statuses();
  $results = static_get_status();

  $form['status'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Status'),
  );

  foreach ($results as $result) {
    if ($result->status == STATIC_EXPIRED) {
      $form['status']['result_' . $result->status] = array(
        '#markup' => t('@count items need publishing.', array('@count' => $result->count, '!status' => $result->status)),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
    }
    else {
      if (isset($statuses[$result->status])) {
        $status = $statuses[$result->status] . ' (' . $result->status . ')';
      }
      else {
        $status = 'Unknown Status (' . $result->status . ')';
      }
      $status =
      $form['status']['result_' . $result->status] = array(
        '#markup' => t('@count items returned !status.', array('@count' => $result->count, '!status' => $status)),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
    }

    $total += $result->count;
  }

  $form['status']['total'] = array(
    '#markup' => t('@total total items.', array('@total' => $total)),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );

  $form['actions'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Actions'),
  );

  $form['actions']['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Publish now'),
  );

  $form['actions']['refresh_paths'] = array(
    '#type' => 'submit',
    '#value' => t('Refresh path list'),
  );

  $form['actions']['regenerate'] = array(
    '#type' => 'submit',
    '#value' => t('Queue all items for regeneration'),
  );

  $form['actions']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Clear all generated data'),
  );

  return $form;
}

/**
 * Form submission handler for static_admin_index_status_form().
 *
 * @see static_admin_index_status_form_validate()
 */
function static_admin_status_submit(array $form, array &$form_state) {
  $values = $form_state['values'];
  $form_state['redirect'] = 'admin/config/system/static';

  switch ($values['op']) {
    case t('Publish now'):
      $result = db_select('static', 's')
        ->fields('s')
        ->condition('status', 0)
        ->execute();
      $count = $result->rowCount();
      _static_batch_generating_create($count);
      break;

    case t('Refresh path list'):
      _static_batch_refresh_paths();
      break;

    case t('Queue all items for regeneration'):
      $form_state['redirect'] .= '/regenerate';
      break;

    case t('Clear all generated data'):
      $form_state['redirect'] .= '/clear';
      break;
  }
}

/**
 * Form constructor for a generic confirmation form.
 */
function static_admin_confirm(array $form, array &$form_state, $action) {
  switch ($action) {
    case 'regenerate':
      $text = array(
        t('Re-generate static pages'),
        t('Do you really want to queue all pages for re-generation?'),
        t('This will mark all items to be regenerated. Old files will still exist until the new ones are regenerated.'),
        t('The pages were successfully marked for re-generation.'),
      );
      break;

    case 'clear':
      $text = array(
        t('Clear static cache'),
        t('Do you really want to clear the entire static cache?'),
        t('This will remove all files that are currently generated. Before the pages is regenerated, there wont be any files if the files are publicly visible. This action cannot be undone.'),
        t('The cache was successfully deleted.'),
      );
      break;

    default:
      return FALSE;
  }
  $form = array(
    'action' => array(
      '#type' => 'value',
      '#value' => $action,
    ),
    'message' => array(
      '#type' => 'value',
      '#value' => $text[3],
    ),
  );
  $desc = "<h3>{$text[1]}</h3><p>{$text[2]}</p>";
  return confirm_form($form, filter_xss($text[0]), "admin/config/system/static", filter_xss($desc));
}

/**
 * Submit function for static_admin_confirm().
 */
function static_admin_confirm_submit(array $form, array &$form_state) {
  $form_state['redirect'] = 'admin/config/system/static';

  $values = $form_state['values'];

  $action = $values['action'];

  $function = "static_{$action}";
  if ($function()) {
    drupal_set_message($values['message']);
  }
  else {
    drupal_set_message(t('An error has occurred while performing the desired action. Check the logs for details.'), 'error');
  }
}

/**
 * Page callback for static status.
 */
function static_admin_paths_list() {
  // Form to add a path to tracking.
  $form['new'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('exposed-filters')),
    '#title' => 'Add a path',
    '#tree' => TRUE,
  );

  $form['new']['path'] = array(
    '#type' => 'textfield',
    '#title' => 'Path',
  );

  $form['new']['frequency'] = array(
    '#type' => 'textfield',
    '#title' => 'Frequency',
    '#description' => 'How often this field should automatically refresh. Set to 0 for only when expired.',
  );

  $form['new']['priority'] = array(
    '#type' => 'textfield',
    '#title' => 'Priority',
    '#description' => 'Set the priority for this path.',
    '#default_value' => 0,
  );

  $form['new']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );

  $session = isset($_SESSION['static_path_filter']) ? $_SESSION['static_path_filter'] : array();

  $session += array(
    'status' => '',
    'path' => '',
    'alias' => '',
  );

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#attributes' => array('class' => array('exposed-filters')),
    '#title' => t('Show only items where'),
  );

  $form['filters']['filters'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#attributes' => array('class' => array('filters')),
  );

  $options = static_statuses();
  foreach ($options as $key => $value) {
    $options[$key] = '(' . $key . ') ' . $value;
  }

  $options = array('' => 'any') + $options;

  $form['filters']['filters']['status'] = array(
    '#type' => 'select',
    '#title' => 'status',
    '#options' => $options,
    '#default_value' => $session['status'],
  );

  $form['filters']['filters']['path'] = array(
    '#type' => 'textfield',
    '#title' => 'path',
    '#size' => 30,
    '#default_value' => $session['path'],
  );

  $form['filters']['filters']['alias'] = array(
    '#type' => 'textfield',
    '#title' => 'alias',
    '#size' => 30,
    '#default_value' => $session['alias'],
  );

  $form['filters']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => count(array_filter($session)) ? t('Refine') : t('Filter'),
  );
  if (count(array_filter($session))) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['status']['actions']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
  );
  $options = array(
    'regenerate_paths' => 'Regenerate Paths',
    'delete_paths' => 'Delete Paths',
    'set_priority' => 'Set Priority',
    'unset_priority' => 'Unset Priority',
  );
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  // Build the sortable table header.
  $header = array(
    'path' => array('data' => t('Path'), 'field' => 's.path'),
    'alias' => array('data' => t('Alias'), 'field' => 's.alias'),
    'file' => array('data' => t('Generated File'), 'field' => 's.file'),
    'frequency' => array('data' => t('Frequency'), 'field' => 's.frequency'),
    'priority' => array('data' => t('Priority'), 'field' => 's.priority'),
    'status' => array('data' => t('Status'), 'field' => 's.status'),
    'status_message' => array('data' => t('Message')),
    'updated' => array(
      'data' => t('Updated'),
      'field' => 's.updated',
      'sort' => 'desc',
    ),
  );

  $query = db_select('static', 's')
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->fields('s');
  $options = array();
  foreach ($session as $index => $filter) {
    if ($filter == '') {
      continue;
    }
    switch ($index) {
      case 'status':
        $query->condition('s.' . $index, $filter);
      case 'path':
      case 'alias':
        $query->condition('s.' . $index, '%' . $filter . '%', 'LIKE');
        break;
    }
  }

  $infos = $query
    ->limit(50)
    ->orderByHeader($header)
    ->execute()
    ->fetchAll();

  $destination = drupal_get_destination();
  foreach ($infos as $info) {
    $options[$info->id] = array(
      'path' => check_plain($info->path),
      'alias' => check_plain($info->alias),
      'file' => check_plain($info->file),
      'frequency' => $info->frequency,
      'priority' => $info->priority,
      'status' => $info->status,
      'status_message' => $info->status_message,
      'updated' => format_date($info->updated, 'short'),
    );
  }

  $form['items'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No content available.'),
  );

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/**
 * Submit handler for static_admin_paths_list().
 */
function static_admin_paths_list_submit($form, &$form_state) {
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      $_SESSION['static_path_filter'] = $form_state['values']['filters'];
      break;

    case t('Reset'):
      $_SESSION['static_path_filter'] = array();
      break;

    case t('Add'):
      static_track_path($form_state['values']['new']);
      break;

    case t('Update'):
      switch ($form_state['values']['operation']) {
        case 'regenerate_paths':
          $items = array_filter($form_state['values']['items']);
          if (empty($items)) {
            break;
          }

          foreach ($items as $item) {
            $static_info = static_load($item);
            $static_info['status'] = 0;
            static_save_info($static_info);

            $result = static_generate_file($static_info['path']);

            if ($result) {
              drupal_set_message('Successfully generated ' . $static_info['path']);
            }
            else {
              drupal_set_message('Unable to generate ' . $static_info['path'], 'error');
            }
          }
          break;

        case 'delete_paths':
          // Need to add a confirm form here as well as instructions that it
          // doesn't delete the generated files as well yet.
          static_delete_multiple($form_state['values']['items']);
          break;

        case 'set_priority':
          $items = array_filter($form_state['values']['items']);
          if (empty($items)) {
            break;
          }
          db_update('static')
            ->fields(array('priority' => 1))
            ->condition('id', $items)
            ->execute();
          break;

        case 'unset_priority':
          $items = array_filter($form_state['values']['items']);
          if (empty($items)) {
            break;
          }
          db_update('static')
            ->fields(array('priority' => 0))
            ->condition('id', $items)
            ->execute();
          break;

      }
      break;
  }
}
