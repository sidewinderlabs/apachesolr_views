<?php

// $Id: apachesolr_views_handler_filter_type.inc,v 1.6 2009/08/17 18:54:23 scottreynolds Exp $

/**
* Class for filtering by type.
*/
class apachesolr_views_handler_filter_type extends views_handler_filter_in_operator {
 
  public function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Node type');
      $types = node_get_types();
      foreach ($types as $type => $info) {
        $options[$type] = $info->name;
      }
      $this->value_options = $options;
    }
  }
  
  /**
   * Provide inclusive/exclusive matching
   * TODO: cannot handle exlusive currently
   *
   * Perhaps use boolean logic to reverse the Not one of to One of all the rest?
   */
  function operator_options() {
    return array(
      'in' => t('Is one of'),
    );
  }

  public function query() {
    if (empty($this->value) && ($this->options['exposed'] && empty($this->options['expose']['optional']))) {
      // Add term that will yield no results
      $this->query->add_filter('nid', apachesolr_views_query::escape_term('-1'));
    }
    else {
      foreach ($this->value as $type) {
        $filter .= " OR $type";
      }
      /**
       * This works, but breaks the facet blocks
       * $this->query->add_filter($this->real_field, substr($filter, 3));
       */
      
      $this->get_value_options();
      foreach ($this->value_options as $type => $name) {
        if (!in_array($type, $this->value)) {
          $this->query->add_filter($this->real_field, $type, TRUE);
        }
      }
    }
  }
}