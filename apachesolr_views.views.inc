<?php
// $Id: apachesolr_views.views.inc,v 1.24 2010/12/15 12:51:35 kenorb Exp $

/*
 * Load files with base classes of the contained classes.
 */

/**
 * Implementation of hook_views_handlers().
 */
function apachesolr_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'apachesolr_views') . '/handlers',
    ),
    'handlers' => array(
      'apachesolr_views_handler_argument_optionwidget' => array(
        'parent' => 'apachesolr_views_handler_argument',
      ),
      'apachesolr_views_handler_argument_node_type' => array(
        'parent' => 'apachesolr_views_handler_argument',
      ),
      'apachesolr_views_handler_argument' => array(
        'parent' => 'views_handler_argument',
      ),
      'apachesolr_views_handler_argument_mlt' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'apachesolr_views_handler_argument_tid' => array(
        'parent' => 'apachesolr_views_handler_argument',
      ),
      'apachesolr_views_handler_argument_search' => array(
        'parent' => 'apachesolr_views_handler_argument',
      ),
      'apachesolr_views_handler_field' => array(
        'parent' => 'views_handler_field_node',
      ),
      'apachesolr_views_handler_field_title' => array(
        'parent' => 'views_handler_field_node',
      ),
      'apachesolr_views_handler_field_author' => array(
        'parent' => 'apachesolr_views_handler_field',
      ),
      'apachesolr_views_handler_field_date' => array(
        'parent' => 'apachesolr_views_handler_field',
      ),
      'apachesolr_views_handler_field_taxonomy' => array(
        'parent' => 'apachesolr_views_handler_field',
      ),
      // Provide tid filtering to apache solr views
      'apachesolr_views_handler_field_tid' => array(
        'parent' => 'views_handler_field',
      ),
      'apachesolr_views_handler_field_type' => array(
        'parent' => 'apachesolr_views_handler_field',
      ),
      'apachesolr_views_handler_field_score' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'apachesolr_views_handler_field_snippet' => array(
        'parent' => 'views_handler_field',
      ),
      'apachesolr_views_handler_filter_tid' => array(
        'parent' => 'views_handler_filter_term_node_tid',
      ),
      'apachesolr_views_handler_optionwidget_filter' => array(
        'parent' => 'views_handler_filter',
      ),
      'apachesolr_views_handler_filter_author' => array(
        'parent' => 'views_handler_filter_user_name',
      ),
      'apachesolr_views_handler_filter_search' => array(
        'parent' => 'views_handler_filter_search',
      ),
      'apachesolr_views_handler_filter_type' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'apachesolr_views_handler_filter_single' => array(
        'parent' => 'views_handler_filter_string',
      ),
      'apachesolr_views_handler_filter_node_access' => array(
        'parent' => 'views_handler_filter_node_access',
      ),
      'apachesolr_views_handler_filter_boolean' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'apachesolr_views_handler_sort' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function apachesolr_views_views_plugins() {
  return array(
    'module' => 'apachesolr_views',
    'query' => array(
      'apachesolr_views_query' => array(
        'title' => t('Apache Solr Query'),
        'help' => t('Query that allows you to search with Apache Solr.'),
        'handler' => 'apachesolr_views_query',
        'parent' => 'views_query',
      ),
    ),
    'cache' => array(
      'apachesolr-time' => array(
        'path' => drupal_get_path('module', 'apachesolr_views') . '/plugins',
        'title' => t('Time-based Solr Cache'),
        'help' => t('Simple time-based caching of data extension for Solr Views'),
        'handler' => 'apachesolr_views_plugin_cache_time',
        'uses options' => TRUE,
        'base' => array('apachesolr'),
        'parent' => 'time',
        //'help topic' => 'apachesolr-cache-time', // TODO!!!
      ),
    ),
    'argument' => array( 	 
      'handler' => 'apachesolr_views_handler_argument_search', 	 
    ),
  );

}

/**
 * Implementation of hook_views_data().
 */
function apachesolr_views_views_data() {
  foreach (module_invoke_all('apachesolr_entities') as $base_table => $definition) {
    $name = $definition['name'];
    $base_field = $definition['base_field'];
    $data['apachesolr_' . $base_table]['table']['group']  = t('Apache Solr');

    $data['apachesolr_' . $base_table]['table']['base'] = array(
      'query class' => 'apachesolr_views_query',
      'title' => t('Apache Solr @name', array('@name' => $name)),
      'help' => t('Searches the site with the Apache Solr search engine for @name', array('@name' => $name)),
      'field' => $base_field,
    );

    $data['apachesolr_' . $base_table]['nid'] = array(
      'title' => t('Nid'),
      'help' => t('The node ID of the node.'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['title'] = array(
      'title' => t('Title'),
      'help' => t('The title of the node.'),
      'field' => array(
        'handler' => 'apachesolr_views_handler_field_title',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'apachesolr_views_handler_filter_single',
      ),
      'argument' => array(
        'handler' => 'apachesolr_views_handler_argument',
      ),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['created'] = array(
      'title' => t('Creation date'),
      'help' => t('The date the node was created.'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['changed'] = array(
      'title' => t('Updated date'),
      'help' => t('The date the node was last updated.'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['type'] = array(
      'title' => t('Type'),
      'help' => t('The type of a node (for example, "blog entry", "forum post", "story", etc).'),
      'argument' => array(
        'handler' => 'apachesolr_views_handler_argument_node_type',
      ),
      'field' => array(
        'handler' => 'views_handler_field_node_type',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'apachesolr_views_handler_filter_type',
      ),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['name'] = array(
      'title' => t('Author'),
      'help' => t("The node's author."),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    $data['apachesolr_' . $base_table]['uid'] = array(
      'title' => t('Author Uid'),
      'help' => t("The node's author's user ID."),
      'argument' => array(
        'handler' => 'apachesolr_views_handler_argument',
      ),
    );
    $data['apachesolr_' . $base_table]['comment_count'] = array(
      'title' => t('Comment count'),
      'help' => t('The number of comments that were posted to the node.'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
    );
    // TODO Get taxonomy fields to work
    if (module_exists('taxonomy')) {
      $data['apachesolr_' . $base_table]['tid'] = array(
        'title' => t('Taxonomy terms'),
        'help' => t('Taxonomy terms associated with the node.'),
        'field' => array(
          'handler' => 'apachesolr_views_handler_field_tid',
          'numeric' => TRUE,
          'click sortable' => TRUE,
          'apachesolr base handler' => array(
            'table' => 'term_node',
            'field' => 'tid',
          ),
        ),
        'argument' => array(
          'handler' => 'apachesolr_views_handler_argument_tid',
        ),
        'filter' => array(
          'handler' => 'apachesolr_views_handler_filter_tid',
        ),
      );
    }
    // @TODO: handle language field.
  
    $data['apachesolr_' . $base_table]['text'] = array(
      'title' => t('Search'),
      'help' => t('Searches the content with Solr'),
      'filter' => array(
        'handler' => 'apachesolr_views_handler_filter_search',
      ),
    );
  
    // score field. Useful for when combining sorts. So you sort by score, creation etc.
    $data['apachesolr_' . $base_table]['score'] = array(
      'title' => t('Search Score'),
      'help' => t('The score of the search for this item. When no sorts are present this is the default sort'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
      'field' => array(
        'handler' => 'apachesolr_views_handler_field_score'
      ),
    );
  
    // comment_count field useful for sorting
    $data['apachesolr_' . $base_table]['comment_count'] = array(
      'title' => t('Comment Count'),
      'help' => t('The number of comments on a node'),
      'sort' => array(
        'handler' => 'apachesolr_views_handler_sort',
      ),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => FALSE,
      ),
    );
  
    // snippet field
    $data['apachesolr_' . $base_table]['snippet'] = array(
      'title' => t('Search Snippet'),
      'help' => t('The return snippet that matches the query sent to Solr.'),
      'field' => array(
        'handler' => 'apachesolr_views_handler_field_snippet',
      ),
    );
    $data['apachesolr_' . $base_table]['mlt'] = array(
      'title' => t('More Like This Node id'),
      'help' => t('Do a more like this query based on the provided nid'),
      'argument' => array(
        'handler' => 'apachesolr_views_handler_argument_mlt',
      ),
    );
  
    // node access
    if (module_exists('apachesolr_nodeaccess')) {
      $data['apachesolr_' . $base_table]['access'] = array(
        'title' => t('Node Access Control'),
        'help' => t('Return results from Apache Solr that respect node access'),
        'filter' => array(
          'handler' => 'apachesolr_views_handler_filter_node_access',
        ),
      );
    }
  
    $data['apachesolr_' . $base_table]['promote'] = array(
      'title' => t('Promoted to Front Page'),
      'help' => t('Whether or not this node was promoted to the front page'),
      'filter' => array(
        'handler' => 'apachesolr_views_handler_filter_boolean',
        'label' => t('Promoted'),
        'type' => 'yes-no',
      ),
    );
  
    // provide CCK mappings filters
    foreach (apachesolr_cck_fields() as $name => $field) {
      // TODO: can we make use of CCK's mapping already and just override
      // the query part???
      $options = content_allowed_values(content_fields($field['field_name']));
      if (!empty($options)) {
        $label = (isset($field['widget']['label'])) ? t($field['widget']['label']) : '';
        $data['apachesolr_' . $base_table][apachesolr_index_key($field)] = array(
          'title' => $label,
          'help' => t('CCK Mapping for @fieldname', array('@fieldname' => $field['field_name'])),
          'filter' => array(
            'handler' => 'apachesolr_views_handler_optionwidget_filter',
            'cck_field' => $field,
          ),
          'argument' => array(
            'handler' => 'apachesolr_views_handler_argument_optionwidget',
            'cck_field' => $field,
          ),
        ); // end: array
      } // end: if
    } // end: foreach
  } // end: foreach
  
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function apachesolr_views_views_data_alter(&$data) {
  // Currently only looking at base table of node.
  $base_tables = array_keys(module_invoke_all('apachesolr_entities'));
  $new_tables = array();
  foreach ($data as $table => $table_definition) {
    // Determine if this is one of our base tables.
    $is_base_table = in_array($table, $base_tables);
    $intersect = array();

    // See if this normal SQL table can join to one of our base tables.
    if (isset($table_definition['table']) && isset($table_definition['table']['join']) && is_array($table_definition['table']['join'])) {
      $intersect = array_intersect($base_tables, array_keys($table_definition['table']['join']));
    }

    if ($is_base_table) {
      $intersect[] = $table;
    }

    if (!empty($intersect)) {
      foreach ($intersect as $base_table) {
        $default_group = $table_definition['table']['group'];
        foreach ($table_definition as $database_field => $definition) {
          if ($database_field != 'table' && isset($definition['field'])) {
            if (!isset($definition['group'])) {
              $definition['group'] = $default_group;
            }

            // Only allow title, help, group and field keys. Filters and sorts are
            // not doable.
            foreach (array('title', 'help', 'group', 'field') as $allowed_key) {
              if ( isset($definition[$allowed_key])) {
                $new_tables['apachesolr_' . $base_table . '_' . $table][$database_field][$allowed_key] = $definition[$allowed_key];
              }
            }

            // Add to the new_tables. This will be merged into data at the end.
            // This prevents and infinite loop.
            $new_tables['apachesolr_' . $base_table . '_' . $table]['table']['join'] = array(
              'apachesolr_' . $base_table => array(
                'left_table' => $table,
              ),
            );

            // If it isn't the base table provide the know how to join it to the
            // SQL query.
            if ($base_table != $table) {
              $new_tables['apachesolr_' . $base_table . '_' . $table]['table']['join'][$base_table] = array_merge(array('table' => $table), $data[$table]['table']['join'][$base_table]);
            }
          }
        }
      }
    }
  }
  $data += $new_tables;
}

/**
 * Implementation of hook_views_plugins_alter().
 */
function apachesolr_views_views_plugins_alter(&$plugins) {
  // Add apachesolr to the base of the node row plugin.
  $plugins['row']['node']['base'][] = 'apachesolr_node';
  $plugins['row']['node_rss']['base'][] = 'apachesolr_node';
}

