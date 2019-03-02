<?php 
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

require( '../../../../wp-load.php' );
global $wpdb;

// locate the email address to be removed.
$contact_id = $_GET['contact_id'] ;
$method     = $_GET['method'] ;

if ($method == 1) { // email unsubscription coming in
    $unsub_confirm_page = site_url() . "/email-unsubscribe" ;    
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts` 
        SET `email` = %s, `email_confirmed` = %s  
        WHERE `ringcentral_contacts_id` = %d",
        "", "", $contact_id) ;
} elseif ($method == 2) { // sms unsubscription coming in
    $unsub_confirm_page = site_url() . "/mobile-unsubscribe" ;
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts`
        SET `mobile` = %s, `mobile_confirmed` = %s
        WHERE `ringcentral_contacts_id` = %d",
        "", "", $contact_id) ;    
}

$wpdb->query($sql);

// then re-direct to public page confirming the email removal.
header("Location: $unsub_confirm_page");

?>