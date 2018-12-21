<?php 
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */
// Include Libraries
require('includes/vendor/autoload.php');

// get control data
global $wpdb;

$result_rc = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `ringcentral_control`
    WHERE `ringcentral_control_id` = %d", 1)
);

$client_id             = $result_rc->client_id ;
$client_secret         = $result_rc->client_secret ;
$ringcentral_user_name = $result_rc->ringcentral_user_name ;
$ringcentral_extension = $result_rc->ringcentral_extension ;
$ringcentral_password  = $result_rc->ringcentral_password ;

// Setup Client
$sdk = new RingCentral\SDK\SDK($client_id, $client_secret, RingCentral\SDK\SDK::SERVER_SANDBOX);

// Login via API
if (!$sdk->platform()->loggedIn()) {
    $sdk->platform()->login($ringcentral_user_name, $ringcentral_extension, $ringcentral_password);
}
return $sdk ;
?>