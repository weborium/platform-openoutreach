<?php
// $Id$

/**
 * @file
 *
 * These functions implement a drush command to send a notification message to the
 * user (client) who has requested the new drupal site once it has been prepared.
 * This code is a modified copy of the functions from hosting_profile_roles.drush.inc
 */

/**
 * Implementation of hook_drush_command().
 */
function hosted_site_drush_command() {
  $items['notify-new-site'] = array(
    'aliases' => array('notify'),
    'description' => dt('Send email to client notifying of the creation of their new Drupal website.'),
    'arguments' => array(
      'name' => dt('The name of the account to send the notification to.'),
    ),
    'options' => array(
      'message' => dt('The message to send.
    allowed values: - "register_admin_created (default)"
                    - "register_no_approval_required"
                    - "register_pending_approval"
                    - "status_activated"'),
    ),
  );
  return $items;
}

/**
 * Drush command to send notification emails
 */
function drush_hosted_site_notify_new_site($name) {
  $message = drush_get_option('message');
  $message_options = array(
    'register_admin_created' => 'Welcome message for user created by the admin',
    'register_no_approval_required' => 'Welcome message when user self-registers',
    'register_pending_approval' => 'Welcome message, user pending admin approval',
    'status_activated' => 'Account activated',
  );
  if ($message == FALSE) {
    // set a default message
    $message = 'status_activated';
  }
  elseif ($message === TRUE) {
    $message = drush_choice($message_options, 'Enter a number to choose which message to send.', '!value (!key)');
  }
  elseif (!array_key_exists($message, $message_options)) {
    return drush_set_error($message . ' is not a valid message!');
  }
  _user_mail_notify($message, user_load(array('name' => $name)));
  drush_print(' Sent notification: ' . $message_options[$message] . ' (' . $message . ')');
  return NULL;
}
