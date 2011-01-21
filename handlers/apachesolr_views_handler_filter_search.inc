<?php

/* $Id: apachesolr_views_handler_filter_search.inc,v 1.3 2010/08/07 23:31:13 scottreynolds Exp $ */

/**
 * Class that allows searching the site with Apache Solr through a view.
 */
class apachesolr_views_handler_filter_search extends views_handler_filter_search {
  
  public function query() {
    if (!empty($this->value)) {
      $this->query->set_query($this->value);
    }
  }
  
   /**
   * Validate the options form.
   */
  function exposed_validate($form, &$form_state) {
    // Don't let Views do anything if the operator is required and nothing has
    // been supplied in the exposed form.
    if (empty($form_state['values'][$this->options['expose']['identifier']]) && $this->options['operator'] == 'required') {
      $this->view->executed = TRUE;
    }
  }
  
}
