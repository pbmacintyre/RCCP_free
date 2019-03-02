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
$token_id = $_GET['contact_id'] ;
$method     = $_GET['method'] ;
$opt_in_date = date('Y-m-d'); // YYYY-MM-DD
$opt_in_ip = $_SERVER['REMOTE_ADDR']?:($_SERVER['HTTP_X_FORWARDED_FOR']?:$_SERVER['HTTP_CLIENT_IP']);  ;

if ($method == 1) { // email confirmation coming in
    $confirmation_page = site_url() . "/email-confirmation" ;    
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts` 
        SET `email_confirmed` = %d, `email_optin_ip` = %s, `email_optin_date` = %s 
        WHERE `ringcentral_token` = %s",
        1, $opt_in_ip, $opt_in_date, $token_id ) ;    
} elseif ($method == 2) { // mobile confirmation coming in
    $confirmation_page = site_url() . "/mobile-confirmation" ;    
    $sql = $wpdb->prepare("UPDATE `ringcentral_contacts`
        SET `mobile_confirmed` = %d, `mobile_optin_ip` = %s, `mobile_optin_date` = %s 
        WHERE `ringcentral_token` = %s",
        1, $opt_in_ip, $opt_in_date, $token_id ) ;
}

$wpdb->query($sql);

// then re-direct to public page confirming the appropriate opt-in method.
header("Location: $confirmation_page");
?>