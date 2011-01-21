<?php

/* $Id: apachesolr_views_handler_filter_author.inc,v 1.6 2009/09/10 20:52:46 scottreynolds Exp $ */

/**
 * Class for filtering by users.
 */
class apachesolr_views_handler_filter_author extends views_handler_filter_user_name {

  public function query() {
    
    $not = $this->operator == 'not in';
    $uids = $this->value;
    
    if (empty($uids) && ($this->options['exposed'] && empty($this->options['expose']['optional']))) {
      if (!$not) {
        $this->query->add_filter('nid', apachesolr_views_query::escape_term('-1'));
      }
    }
    else {
      foreach ($uids as $uid) {
        $filter_string .= " OR $uid";
      }
      // construct a small subquery
      $filter_string = substr($filter_string, 4);
      $filter_string = "($filter_string)";
      
      // add it to the query
      $this->query->add_filter('uid', $filter_string, $not);
    }
  }
}
