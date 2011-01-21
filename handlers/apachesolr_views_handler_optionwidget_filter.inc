<?php
// $Id: apachesolr_views_handler_optionwidget_filter.inc,v 1.1 2009/05/12 18:28:29 scottreynolds Exp $
class apachesolr_views_handler_optionwidget_filter extends views_handler_filter {
  /**
   * override query
   */
  function query() {
    $this->query->add_filter($this->real_field, $this->value);
  }
  
  /**
   * Provide a simple textfield for equality
   */
  function value_form(&$form, &$form_state) {
    // parent::value_form doesn't return anything
    // SIGH! definition['cck_field'] doesn't have 'allowed_values'
    $options = content_allowed_values(content_fields($this->definition['cck_field']['field_name']));
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t($this->definition['cck_field']['label']),
      '#options' => $options,
      '#default_value' => $this->value,
    );
  }
}