<?php
// $Id: apachesolr_views_handler_argument_mlt.inc,v 1.4 2009/11/23 22:37:49 scottreynolds Exp $
class apachesolr_views_handler_argument_mlt extends views_handler_argument_numeric {
  
  /**
   * Override option_definition() to provide defaults
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['mlt_fl'] = array('default' => array('title' => '1.0', 'taxonomy_names' => '1.0'));
    $options['mlt_mintf'] = array('default' => '1');
    $options['mlt_mindf'] = array('default' => '1');
    $options['mlt_minwl'] = array('default' => '3');
    $options['mlt_maxwl'] = array('default' => '15');
    $options['mlt_maxqt'] = array('default' => '30');
    
    // type
    $options['type'] = array('default' => 'node');
    return $options;
  }
  /**
   * Override options form to present specific stuffs
   */
  function options_form(&$form, &$form_state) {
    module_load_include('inc', 'apachesolr', 'apachesolr.admin'); // for apachesolr_mlt_get_fields()
    parent::options_form($form, $form_state);
    // TODO: figure out how to do this. cant do id: 123 id: 456 can we?
    unset($form['break_phrase']);

    // TODO: can we exclude this argument??
    unset($form['not']);
    
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Object type'),
      '#description' => t('Select the object type (node, user) that you will be present in the url '),
      '#options' => array(
        'node' => t('Node'),
        'user' => t('User'),
      ),
      '#default_value' => $this->options['type'],
    );

    // Grab the mlt fields.
    $mlt_fields = apachesolr_mlt_get_fields();
    $weights = drupal_map_assoc(array('21.0', '13.0', '8.0', '5.0', '3.0', '2.0', '1.0', '0.8', '0.5', '0.3', '0.2', '0.1'));
    $weights['0'] = t('Omit');
    $form['mlt_fl'] = array('#type' => 'fieldset', '#tree' => TRUE, '#title' => t('Fields') );
    foreach ($mlt_fields as $key => $description) {
       $form['mlt_fl'][$key] = array(
	 '#type' => 'select',
	 '#options' => $weights,
	 '#title' => $description,
	 '#default_value' => isset($this->options['mlt_fl'][$key]) ? $this->options['mlt_fl'][$key] : '0',
      );
    }
   
    $options = drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7));
    $form['mlt_mintf'] = array(
      '#type' => 'select',
      '#title' => t('Minimum Term Frequency'),
      '#description' => t('A word must appear this many times in any given document before the document is considered relevant for comparison.'),
      '#default_value' => $this->options['mlt_mintf'],
      '#options' => $options,
    );
    $form['mlt_mindf'] = array(
      '#type' => 'select',
      '#title' => t('Minimum Document Frequency'),
      '#description' => t('A word must occur in at least this many documents before it will be used for similarity comparison.'),
      '#default_value' => $this->options['mlt_mindf'],
      '#options' => $options,
    );
    $form['mlt_minwl'] = array(
      '#type' => 'select',
      '#title' => t('Minimum Word Length'),
      '#description' => 'You can use this to eliminate short words such as "the" and "it" from similarity comparisons. Words must be at least this number of characters or they will be ignored.',
      '#default_value' => $this->options['mlt_minwl'],
      '#options' => $options,
    );
    $form['mlt_maxwl'] = array(
      '#type' => 'select',
      '#title' => t('Maximum World Length'),
      '#description' => t('You can use this to eliminate very long words from similarity comparisons. Words of more than this number of characters will be ignored.'),
      '#default_value' => $this->options['mlt_maxwl'],
      '#options' => drupal_map_assoc(array(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)),
    );
    $form['mlt_maxqt'] = array(
      '#type' => 'select',
      '#title' => t('Maximum number of query terms'),
      '#description' => t('The maximum number of query terms that will be included in any query. Lower numbers will result in fewer recommendations but will get results faster. If a content recommendation is not returning any recommendations, you can either check more "Comparison fields" checkboxes or increase the maximum number of query terms here.'),
      '#options' => drupal_map_assoc(array(5, 10, 15, 20, 25, 30, 35, 40, 45, 50)),
      '#default_value' => $this->options['mlt_maxqt'],
    );
  }
  
  /**
   * Override query().
   */
  function query() {
    $mlt_specific_options = array(
      'mlt_mintf' => 'mlt.mintf',
      'mlt_mindf' => 'mlt.mindf',
      'mlt_minwl' => 'mlt.minwl',
      'mlt_maxwl' => 'mlt.maxwl',
      'mlt_maxqt' => 'mlt.maxqt',
      'mlt_boost' => 'mlt.boost',
      'mlt_qf' => 'mlt.qf',
    );
    $this->query->change_query_template('mlt');
    $mlt = array();
    $field_boosts = array(); 
    // Set the boosts for each selected field.
    foreach (array_filter($this->options['mlt_fl']) as $field => $boost) {
      $mlt[] = $field;
      $field_boosts[] = "$field^$boost";
    }

    $this->query->set_param('mlt.fl', implode(',', $mlt));
    $this->query->set_param('mlt.qf', $field_boosts);
    
    // now set the configuration options for the calculation
    foreach ($mlt_specific_options as $form_key => $option_name) {
      if (!empty($this->options[$form_key])) {
        $this->query->set_param($option_name, $this->options[$form_key]);
      }
    }
    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }
    foreach ($this->value as $nid) {
      $this->query->set_query('id:' . apachesolr_document_id($nid, $this->options['type']));
    }
  }
}
?>