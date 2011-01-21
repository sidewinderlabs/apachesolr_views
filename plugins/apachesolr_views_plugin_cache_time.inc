<?php
// $Id: apachesolr_views_plugin_cache_time.inc,v 1.3 2009/08/14 21:51:44 scottreynolds Exp $
/**
 * @file
 * provides Views caching plugin for solr
 */
class apachesolr_views_plugin_cache_time extends views_plugin_cache_time {
  /**
   * Save data to the cache.
   *
   * A plugin should override this to provide specialized caching behavior.
   */
  function cache_set($type) {
    switch ($type) {
      case 'query':
        // Not supported currently, but this is certainly where we'd put it.
        break;
      case 'results':
        $data = array(
          'result' => $this->view->result,
          'total_rows' => $this->view->total_rows,
          'pager' => $this->view->pager,
          'response' => apachesolr_static_response_cache(),
        );
        cache_set($this->get_results_key(), $data, $this->table);
        break;
      case 'output':
        parent::cache_set($type);
        break;
    }
  }


  /**
   * Retrieve data from the cache.
   *
   * A plugin should override this to provide specialized caching behavior.
   */
  function cache_get($type) {
    $cutoff = $this->cache_expire($type);
    switch ($type) {
      case 'query':
        // Currently not supported in base class. but we send it up in case it is
        return parent::cache_get($type);
      case 'results':
        // Values to set: $view->result, $view->total_rows, $view->execute_time,
        // $view->pager['current_page'].
        if ($cache = cache_get($this->get_results_key(), $this->table)) {
          if (!$cutoff || $cache->created > $cutoff) {
            $this->view->result = $cache->data['result'];
            $this->view->total_rows = $cache->data['total_rows'];
            $this->view->pager = $cache->data['pager'];
            apachesolr_static_response_cache($cache->data['response']);
            apachesolr_current_query($this->view->query);
            $this->view->execute_time = 0;
            apachesolr_has_searched(TRUE);
            return TRUE;
          }
        }
        return FALSE;
      case 'output':
        return parent::cache_get($type);
    }
  }
}
?>