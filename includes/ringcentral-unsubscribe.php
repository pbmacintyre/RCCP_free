<?php 
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

require( '../../../../wp-load.php' );
global $wpdb;

// locate the email address to be removed.
$contact_id = $_GET['contact_id'] ;
$method     = $_GET['method'] ;

if ($method == 1) { // email unsubscription coming in
    $unsub_confirm_page = site_url() . "/email-unsubscribe" ;    
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts` 
        SET `email` = %s, `email_confirmed` = %d,`email_optin_ip` = %s, `email_optin_date` = %s  
        WHERE `ringcentral_token` = %s",
        "", 0, "", "", $contact_id) ;    
} elseif ($method == 2) { // sms unsubscription coming in
    $unsub_confirm_page = site_url() . "/mobile-unsubscribe" ;
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts`
        SET `mobile` = %s, `mobile_confirmed` = %d,`mobile_optin_ip` = %s, `mobile_optin_date` = %s
        WHERE `ringcentral_token` = %s",
        "", 0, "", "", $contact_id) ;
}

$wpdb->query($sql);

/* check to see if the contact should be removed altogether */
$contact = $wpdb->get_results( $wpdb->prepare("SELECT * FROM `ringcentral_contacts` WHERE `ringcentral_token` = %s", $contact_id ) );
if ($contact->email == "" && $contact->mobile == "" && $contact->email_confirmed == 0 && $contact->mobile_confirmed == 0 ) {
    $sql = $wpdb->prepare("DELETE FROM `ringcentral_contacts` WHERE `ringcentral_token` = %s", $contact_id) ;
    $wpdb->query($sql);
}

// then re-direct to public page confirming the email removal.
header("Location: $unsub_confirm_page");

?>