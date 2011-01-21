<?php
// $Id: apachesolr_views_handler_filter_node_access.inc,v 1.1 2009/08/14 21:51:44 scottreynolds Exp $

/**
 * @file
 * provides node access filter implementation for apache solr
 */
class apachesolr_views_handler_filter_node_access extends views_handler_filter_node_access {
  
  /**
   * Override query().
   */
  function query() {
    try {
      $subquery = _apachesolr_nodeaccess_build_subquery($GLOBALS['user']);
    }
    catch (Exception $e) {
      $query = NULL;
      watchdog("apachesolr_nodeaccess", 'User %name (UID:!uid) cannot search: @message', array('%name' => $user->name, '!uid' => $user->uid, '@message' => $e->getMessage()));
      return;
    }

    if (!empty($subquery)) {
      $this->query->add_subquery($subquery, 'OR');
    }
  }
}
?>