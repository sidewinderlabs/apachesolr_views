<?php
// $Id: apachesolr_views_handler_filter_single.inc,v 1.2 2009/08/14 21:51:44 scottreynolds Exp $

/**
 * generic filter for Apache Solr
 */
class apachesolr_views_handler_filter_single extends views_handler_filter_string {
  
  /**
   * override query().
   */
  function query() {
    if ($this->operator == '!=') {
      $field = "NOT " . $this->value['value'];
    }
    else {
      $field = $this->value['value'];
    }
    $this->query->add_filter($this->real_field, $field);
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['case']);
  }
  
  /**
   * Override the operators
   */
  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'short' => t('='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'short' => t('!='),
        'method' => 'op_equal',
        'values' => 1,
      ),
    );
    return $operators;
  }
}