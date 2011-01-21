<?php
// $Id: apachesolr_views_handler_field_title.inc,v 1.1 2010/12/15 10:39:22 kenorb Exp $

/**
 * @file
 * Views handler to handle the title field. Will not add anything to the query
 */
class apachesolr_views_handler_field_title extends views_handler_field_node {
  function construct() {
    parent::construct();
  }
  function query() {
    $this->field_alias = $this->query->add_solr_field('title');
  }

  function render_link($data, $values) {
    if (!empty($this->options['link_to_node']) && $data !== NULL && $data !== '') {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "node/" . $values->nid;
      if (isset($this->aliases['language'])) {
        $languages = language_list();
        if (isset($languages[$values->{$this->aliases['language']}])) {
          $this->options['alter']['language'] = $languages[$values->{$this->aliases['language']}];
        }
        else {
          unset($this->options['alter']['language']);
        }
      }
    }
    return $data;
  }
}

