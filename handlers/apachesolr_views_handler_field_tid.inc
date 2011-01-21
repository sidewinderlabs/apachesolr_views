<?php

// Based on jtsnow's patch on http://drupal.org/node/566692

class apachesolr_views_handler_field_tid extends views_handler_field {

  function query() {
    $this->field_alias = $this->query->add_field('tid');
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    $terms = array();
    if (is_array($value)) {
      foreach($value as $tid) {
        $term = taxonomy_get_term($tid);
        $terms[] = $term->name;
      }
    }
    return implode(', ', $terms);
  }

}
