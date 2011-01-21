<?php

// $Id: apachesolr_views_handler_field_snippet.inc,v 1.3 2010/05/10 21:31:54 scottreynolds Exp $

/**
 * @file
 * provides a field handler for the snippet coming from the ApacheSolr search engine
 */
class apachesolr_views_handler_field_snippet extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['num_snippets'] = array('default' => 1);
    $options['fragsize'] = array('default' => 100);
    $options['merge'] = array('default' => 'true');
    $options['tag'] = array('default' => 'em');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['num_snippets'] = array(
      '#title' => t('Number of snippets to return'),
      '#type' => 'select',
      '#options' => drupal_map_assoc(range(1, 5)),
      '#default_value' => $this->options['num_snippets'],
      '#description' => t('The maximum number of highlighted snippets to generate'),
    );

    $form['fragsize'] = array(
      '#title' => t('Fragment Size'),
      '#type' => 'textfield',
      '#default_value' => $this->options['fragsize'],
      '#description' => t('The size in characters, of fragments for highlighting'),
    );

    $form['merge'] = array(
      '#title' => t('Merge Contiguous Fragments'),
      '#type' => 'radios',
      '#default_value' => $this->options['merge'],
      '#options' => array(
        'true' => t('Merge fragments'),
        'false' => t('Do not merge fragments'),
      ),
      '#description' => t('Collapse contiguous fragments into one fragment'),
    );

    $form['tag'] = array(
      '#title' => t('Tag for matching words'),
      '#type' => 'textfield',
      '#default_value' => $this->options['tag'],
      '#description' => t('HTML tag to surround the matching words in the snippet'),
    );
  }

  function query() {
    // Wierd that with ht.alternateField we can't have the snippet be the body...
    $this->query->add_solr_field('body');
    $this->query->set_param('hl.snippets', $this->options['num_snippets']);
    $this->query->set_param('hl.fragsize', $this->options['fragsize']);
    $this->query->set_param('hl.mergeContiguous', $this->options['merge']);
    $this->query->set_param('hl.simple.pre', '<' . $this->options['tag'] . '>');
    $this->query->set_param('hl.simple.post', '</' . $this->options['tag'] . '>');
  }
  
  function render($doc) {
    $response = apachesolr_static_response_cache();
    $hl_fl = $this->query->get_param('hl.fl');
    if (is_null($hl_fl)) {
      $hl_fl = 'body';
    }
    $snippet = isset($response->highlighting->{$doc->id}->$hl_fl) ? theme('apachesolr_search_snippets', $doc, $response->highlighting->{$doc->id}->$hl_fl) : $doc->body;
    
    return $snippet;
  }
}