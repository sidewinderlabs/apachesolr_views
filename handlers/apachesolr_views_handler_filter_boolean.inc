<?php
// $Id: apachesolr_views_handler_filter_boolean.inc,v 1.1 2009/09/10 20:55:41 scottreynolds Exp $

/**
 * Provides a basic handler for boolean fields
 */
class apachesolr_views_handler_filter_boolean extends views_handler_filter_boolean_operator {
  /**
   * Override query to do our thing
   */
  function query() {
    $this->query->add_filter($this->real_field, $this->value);
  }
}