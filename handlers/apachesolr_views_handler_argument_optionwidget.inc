<?php
// $Id: apachesolr_views_handler_argument_optionwidget.inc,v 1.1 2009/08/14 21:51:44 scottreynolds Exp $

/**
 * @file
 * Provides an argument handler for optionwidgets so they can use their allowed values
 */
class apachesolr_views_handler_argument_optionwidget extends apachesolr_views_handler_argument {
  
  /**
   * Override query() and do some fancy manipulation of the argument
   * so that it is boiled down to the actual field value
   * instead of the nice title
   */
  function query() {
    $field = $this->definition['cck_field'];
    
    foreach (content_allowed_values(content_fields($field['field_name'])) as $allowed_value => $nice_text) {
      $options[$allowed_value] = strtolower(str_replace(' ', '-', $nice_text));
    }
    if (!empty($this->options['break_phrase'])) {
      $arguments = explode(',', $this->get_value());
    }
    else {
      $arguments = array($this->get_value());
    }
    
    // time to set the arguments to something new
    $new_arguments = array();
    foreach ($arguments as $value) {
      $key = array_search($value, $options);
      if (!empty($key)) {
        $new_arguments[] = $key;
      }
      else {
        // TODO: do we need to do something here?
      }
    }
    
     foreach ($new_arguments as $facet_value) {
      $this->query->add_filter($this->real_field, apachesolr_views_query::escape_term($facet_value));
    }
  }
  
  /**
   * Get the title this argument will assign the view, given the argument.
   */
  function title() {
    $field = $this->definition['cck_field'];
    foreach (content_allowed_values(content_fields($field['field_name'])) as $allowed_value => $nice_text) {
      $valid_path = strtolower(str_replace(' ', '-', $nice_text));
      if ($this->argument == $valid_path) {
        return check_plain($nice_text);
      }
    }
    return check_plain($this->argument);
  }

}