<?php

/* $Id: apachesolr_views_handler_field_generic.inc,v 1.3 2010/12/15 10:33:35 kenorb Exp $ */

/**
 * Class for retrieving and rendering an arbitrary field from an Apache Solr
 * query.
 * The class uses a predefined handler to which it acts as a proxy.
 */
class apachesolr_views_handler_field_generic {
  
  /**
   * The handler from which to copy methods.
   */
  private $_original;
  
  /*
   * Overloaded methods (this is where the magic lies)
   */
  
  /**
   * Gets called when trying to retrieve an undefined property.
   */
  public function &__get($name) {
    if (isset($this->_original->$name)) {
      return $this->_original->$name;
    }
    return NULL;
  }
  
  /**
   * Gets called when trying to set an undefined property.
   */
  public function __set($name, $value) {
    $this->_original->$name = $value;
  }
  
  /**
   * Gets called when calling isset() or empty() on an undefined property.
   */
  public function __isset($name) {
    return isset($this->_original->$name);
  }
  
  /**
   * Gets called when calling unser() on an undefined property.
   */
  public function __unset($name) {
    unset($this->_original->$name);
  }
  
  /**
   * Gets called when calling an undefined instance method.
   */
  public function __call($name, $args) {
    if (!method_exists($this->_original, $name)) {
      trigger_error("tried to call undefined instance method $name", E_USER_ERROR);
    }
    return call_user_func_array(array($this->_original, $name), $args);
  }
  
  /**
   * Gets called when calling an undefined static method.
   */
  public static function __callStatic($name, $args) {
    $method = array(get_class($this->_original), $name);
    if (!method_exists($method)) {
      trigger_error("tried to call undefined static method $name", E_USER_ERROR);
    }
    call_user_func_array($method, $args);
  }
  
  /*
   * "Normal" methods
   */
  
  /**
   * Loads the base handler and loads it with the specified definition.
   * Throws an exception if unsuccessful.
   */
  public function set_definition($definition) {
    if (empty($definition['apachesolr base handler'])) {
      watchdog('views',
          'no base handler specified for apachesolr field handler', array(),
          WATCHDOG_ERROR);
    }
    $o = $definition['apachesolr base handler'];
    $this->_original = views_get_handler($o['table'], $o['field'], 'field');
    if (empty($this->_original)) {
      watchdog('views',
          'invalid base handler specified for apachesolr field handler: ' .
          $o['table'] . '/' . $o['field'], array(), WATCHDOG_ERROR);
    }
    // Give the original handler the correct definition.
    $this->_original->set_definition($definition);
  }
  
  /**
   * Get option form definition.
   * 
   * <strong>NOTE:</strong> This method must be defined explicitly since
   * pass-by-reference doesn't work with <tt>call_user_func_array()</tt>.
   */
  public function options_form(&$form, &$form_state) {
    return $this->_original->options_form($form, $form_state);
  }
  
  /**
   * Construct a new apachesolr field handler.
   */
  public function construct() {
    $this->_original->construct();

    $this->_original->aliases = drupal_map_assoc(
        array('id', 'site', 'hash', 'url', 'title', 'body', 'type', 'type_name',
            'path', 'path_alias', 'uid', 'name', 'created', 'changed',
            'last_comment_or_change', 'nid', 'status', 'promote', 'moderate',
            'sticky', 'tnid', 'translate', 'language', 'comment_count', 'tid',
            'vid', 'timestamp'
        ));
  }
  
  /**
   * We don't need to ensure any tables.
   * So overwrite this method because it might be called by inherited methods.
   */
  public function ensure_my_table() {}
  
  /**
   * Tell the query object to retrieve this field.
   */
  public function query() {
    $this->_original->field_alias = $this->_original->real_field;
    $this->_original->query->add_field($this->_original->real_field);
    $this->add_additional_fields();
  }
  
  /**
   * Add additionally required fields.
   */
  public function add_additional_fields($fields = NULL) {
    if (!empty($fields)) {
      return $this->_original->add_additional_fields($fields);
    }
    foreach ($this->_original->additional_fields as $f) {
      $this->_original->query->add_field($f);
    }
  }
  
  /**
   * Called when click-sorting.
   */
  public function click_sort($order) {
    /* These fields have a special "sort_*" field for sorting: */
    $special_sort_fields = array(
      'name' => 'sort_name',
      'title' => 'sort_title',
    );
    
    if (empty($special_sort_fields[$this->real_field])) {
      $this->_original->query->add_sort(
          $this->_original->real_field, $order, TRUE);
    }
    else {
      $this->_original->query->add_sort(
          $special_sort_fields[$this->_original->real_field], $order, TRUE);
    }
  }
  
}
