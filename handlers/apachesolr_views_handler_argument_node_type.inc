<?php
// $Id: apachesolr_views_handler_argument_node_type.inc,v 1.1 2009/09/14 22:26:52 scottreynolds Exp $

/**
 * @file
 * defines a class to handle node type arguments
 */
class apachesolr_views_handler_argument_node_type extends apachesolr_views_handler_argument {
  function title() {
    return $this->node_type($this->argument);
  }

  function node_type($type) {
    $output = node_get_types('name', $type);
    if (empty($output)) {
      return t('Unknown node type');
    }
    else {
      $output .= 's';
      return check_plain(t($output));
    }
  }
}