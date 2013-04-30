<?php
function drush_openoutreach_post_provision_install() {
  // Extract the site uri and drupal install root
  $uri = d()->uri;
  $root = d()->root;
  // Generate a log entry
  drush_log(dt('Profile openoutreach post provision install for @uri',array('@uri'=>$uri)));
  $name = $root . '/sites/' . $uri . '/files/xmlsitemap';
  if (file_exists($name) && is_dir($name)) {
    drush_log(dt('@name exists and is a directory',array('@name'=>$name)));
    if ($handle = opendir($name)) {
      while (false !== ($entry = readdir($handle))) {
        if ($entry != "." && $entry != "..") {
          chgrp($name . '/' . $entry, 'apache');
        }
      }
      closedir($handle);
    }
  }
}
