<?php

// $Id:

/**
 * Class that allows searching the site with Apache Solr through a view argument.
 */
class apachesolr_views_handler_argument_search extends apachesolr_views_handler_argument {
  
  /**
   * Add argument to query.
   */
  public function query() {
    $this->query->set_query(Drupal_Apache_Solr_Service::escape($this->argument));
  }
  
}
