<?php

/* $Id: apachesolr_views_handler_sort.inc,v 1.4 2010/12/15 17:03:46 kenorb Exp $ */

/**
 * Class for sorting for a field.
 */
class apachesolr_views_handler_sort extends views_handler_sort {
  
  /**
   * Places the sort into the search parameters.
   */
  public function query() {
    /* These fields have a special "sort_*" field for sorting: */
    $special_sort_fields = array(
      'name' => 'sort_name',
      'title' => 'sort_title',
    );

    $order = strtolower($this->options['order']);
    $field = empty($special_sort_fields[$this->real_field]) ? $this->real_field : $special_sort_fields[$this->real_field];
    $exposed_data = $this->view->exposed_data;
    $handler = $this->view->sort[$exposed_data['sort_by']];
    
    $this->query->add_sort($field, $order, !empty($handler->options['exposed']));

  }
  
}
