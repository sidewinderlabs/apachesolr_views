<?php
// $Id: apachesolr_views_handler_argument_tid.inc,v 1.6 2009/08/14 21:51:44 scottreynolds Exp $

class apachesolr_views_handler_argument_tid extends apachesolr_views_handler_argument {
  
  function title() {
    if (!empty($this->options['break_phrase'])) {
      $this->value = explode(',', $this->argument);
    }
    else {
      $this->value = array($this->argument);
    }
    $term_names = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));
    
    $result = db_query("SELECT td.name, td.tid FROM {term_data} td WHERE td.tid IN ($placeholders)", $this->value);
    
    while ($term = db_fetch_object($result)) {
      $term_names[$term->tid] = check_plain($term->name);
    }
    return theme('apachesolr_views_term_titles', $term_names);
  }
}