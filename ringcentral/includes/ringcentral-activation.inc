<?php 
/*
 } Copyright (C) 2018 RingCentral Inc.
 }
 */

global $wpdb;

require_once (ABSPATH . 'wp-admin/includes/upgrade.php');

/* ================================= */
/* Create ringcentral_control table  */
/* ================================= */
$ringcentral_sql = "CREATE TABLE `ringcentral_control` (
  `ringcentral_control_id` int(11) NOT NULL AUTO_INCREMENT,
  `embedded_phone` tinyint(4) NOT NULL,
  `client_id` varchar(50) NOT NULL,
  `client_secret` varchar(50) NOT NULL,
  `ringcentral_user_name` varchar(50) NOT NULL,
  `ringcentral_extension` tinyint(4) NOT NULL,
  `ringcentral_password` varchar(50) NOT NULL,
  `email_updates` tinyint(4) NOT NULL,
  `mobile_updates` tinyint(4) NOT NULL,
  `token_prefix` varchar(10) NOT NULL,
  `oauth_client` varchar(75) NOT NULL,
  `oauth_secret` varchar(75) NOT NULL,
  PRIMARY KEY (`ringcentral_control_id`)
) ";
dbDelta($ringcentral_sql);
/* ====================================== */
/* seed table with control row and basic  */
/* data if there is no existing row       */
/* ====================================== */
$row_exists = $wpdb->get_var($wpdb->prepare("SELECT `ringcentral_control_id` FROM `ringcentral_control`
        WHERE `ringcentral_control_id` = %d", 1) );
if (!$row_exists) {
    $wpdb->query( $wpdb->prepare("INSERT INTO `ringcentral_control`
      (`ringcentral_control_id`, `embedded_phone`, `email_updates`, `mobile_updates`)
      VALUES (%d, %d, %d, %d )",
        1, 1, 1, 0 )
        );
}
/* ================================= */
/* Create ringcentral_contacts table */
/* ================================= */
$ringcentral_sql = "CREATE TABLE `ringcentral_contacts` (
  `ringcentral_contacts_id` int(11) NOT NULL AUTO_INCREMENT,
  `ringcentral_token` varchar(33) NOT NULL,
  `full_name` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `email_confirmed` tinyint(4) NOT NULL DEFAULT '0',
  `email_optin_ip` varchar(50) NOT NULL,
  `email_optin_date` varchar(10) NOT NULL,
  `mobile` varchar(25) NOT NULL,
  `mobile_confirmed` tinyint(4) NOT NULL DEFAULT '0',
  `mobile_optin_ip` varchar(50) NOT NULL,
  `mobile_optin_date` varchar(10) NOT NULL,
  PRIMARY KEY (`ringcentral_contacts_id`)
) ";
dbDelta($ringcentral_sql);
/* =======================================*/
/* Create ringcentral_call_requests table */
/* =======================================*/
$ringcentral_sql = "CREATE TABLE `ringcentral_call_requests` (
  `ringcentral_call_requests_id` int(11) NOT NULL AUTO_INCREMENT,
  `full_name` varchar(100) NOT NULL,
  `mobile` varchar(25) NOT NULL,  
  `requested_date` varchar(10) NOT NULL,
  `call_reason` varchar(500) NOT NULL,
  PRIMARY KEY (`ringcentral_call_requests_id`)
) ";
dbDelta($ringcentral_sql);
/* ======================================= */
/* build email confirmation page if needed */
/* ======================================= */
$new_page_title = 'Email Confirmation';
$new_page_content = 'email-confirmed ... thanks for that !';
$new_page_template = '';
$page_check = get_page_by_title($new_page_title);
$new_page = array(
    'post_type' => 'page',
    'post_title' => $new_page_title,
    'post_content' => $new_page_content,
    'post_status' => 'publish',
    'post_author' => 1,
);
if(!isset($page_check->ID)){
    $new_page_id = wp_insert_post($new_page);
    if(!empty($new_page_template)){
        update_post_meta($new_page_id, '_wp_page_template', $new_page_template);
    }
}
/* =================================================== */
/* build email unsubscribe confirmation page if needed */
/* =================================================== */
$new_page_title = 'Email Unsubscribe';
$new_page_content = 'You have been unsubscribed from the email list ... you may still be on the SMS text distribution list.';
$new_page_template = '';
$page_check = get_page_by_title($new_page_title);
$new_page = array(
    'post_type' => 'page',
    'post_title' => $new_page_title,
    'post_content' => $new_page_content,
    'post_status' => 'publish',
    'post_author' => 1,
);
if(!isset($page_check->ID)){
    $new_page_id = wp_insert_post($new_page);
    if(!empty($new_page_template)){
        update_post_meta($new_page_id, '_wp_page_template', $new_page_template);
    }
}
/* ======================================== */
/* build mobile confirmation page if needed */
/* ======================================== */
$new_page_title = 'Mobile Confirmation';
$new_page_content = 'Your mobile device has been confirmed ... thanks for that !';
$new_page_template = '';
$page_check = get_page_by_title($new_page_title);
$new_page = array(
    'post_type' => 'page',
    'post_title' => $new_page_title,
    'post_content' => $new_page_content,
    'post_status' => 'publish',
    'post_author' => 1,
);
if(!isset($page_check->ID)){
    $new_page_id = wp_insert_post($new_page);
    if(!empty($new_page_template)){
        update_post_meta($new_page_id, '_wp_page_template', $new_page_template);
    }
}
/* ==================================================== */
/* build mobile unsubscribe confirmation page if needed */
/* ==================================================== */
$new_page_title = 'Mobile Unsubscribe';
$new_page_content = 'You have been unsubscribed from the mobile list ... you may still be on the email distribution list.';
$new_page_template = '';
$page_check = get_page_by_title($new_page_title);
$new_page = array(
    'post_type' => 'page',
    'post_title' => $new_page_title,
    'post_content' => $new_page_content,
    'post_status' => 'publish',
    'post_author' => 1,
);
if(!isset($page_check->ID)){
    $new_page_id = wp_insert_post($new_page);
    if(!empty($new_page_template)){
        update_post_meta($new_page_id, '_wp_page_template', $new_page_template);
    }
}
?>