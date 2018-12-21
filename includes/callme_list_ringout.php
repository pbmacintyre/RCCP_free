<?php 

require( '../../../../wp-load.php' );
global $wpdb;

require_once("ringcentral-functions.inc");

$to_number = $_GET['to_number'] ;

ringcentral_ringout($to_number);

$return_url = "http://ringc.paladin-bs.com/wp-admin/admin.php?page=ringcentral_list_callme";

// then re-direct back to list page
header("Location: $return_url");

?>