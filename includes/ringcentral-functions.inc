<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

/* ================== */
/* Get RingCental SDK */
/* ================== */
function ringcentral_sdk() {
    // Include Libraries
    require('vendor/autoload.php');
    
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
}
/* =============================== */
/* send out welcome email function */
/* =============================== */
function send_welcome_email($email, $token, $full_name) {
    $confirm_url = plugins_url('/', __FILE__) . "ringcentral-confirm-optin.php?contact_id=" . $token;
    $confirm_url .= "&method=1" ;
    $subject = 'RingCentral - Please confirm your signup';
    
    $message = "Hi $full_name: <br/><br/>Thanks for joining our newsletter sign up process. ";
    $message .= "<br/><strong>[If this was not you please ignore this email]</strong><br/>";
    $message .= "If you also signed up for SMS messaging you will receive a separate confirmation text in that regard.  <br/> ";
    $message .= "<br/>Please follow this link to confirm your subscription to our email notification list: <br/> ";
    $message .= "<a href='$confirm_url'> Confirm sign up </a>";
    
    // Send email to new sign up email.
    $headers = array('Content-Type: text/html; charset=UTF-8');
    wp_mail( $email, $subject, $message, $headers );
} // end send_welcome_email function

/* ============================= */
/* send out welcome SMS function */
/* ============================= */
function send_welcome_mobile($to, $token, $full_name) {
    
    $confirm_url = plugins_url('/', __FILE__) . "ringcentral-confirm-optin.php?contact_id=" . $token;
    $confirm_url .= "&method=2" ;
    $message = "Hi $full_name: Thanks for joining our newsletter sign up process. [If this was not you please ignore this message]\n\n";
    $message .= "If you also signed up for email notifications you will receive a separate confirmation email in that regard.\n\n";
    $message .= "Please follow this link to confirm your SMS subscription to our mailing list: \n\n ";
    $message .= "$confirm_url ";
    
    $from = ringcentral_get_from();
    
    $sdk = ringcentral_sdk() ;
    try {
        // echo "in try...";
        $apiResponse = $sdk->platform()->post('/account/~/extension/~/sms',
            array('from' => array('phoneNumber' => $from),
                'to'   => array( array('phoneNumber' => $to) ),
                'text' => $message ) );
    } catch (\RingCentral\SDK\Http\ApiException $e) {
        
        // Getting error messages using PHP native interface
        //                     print 'Expected HTTP Error: ' . $e->getMessage() . PHP_EOL;
        
        // In order to get Request and Response used to perform transaction:
        $apiResponse = $e->apiResponse();
        //                     print_r($apiResponse->request());
        //                     print_r($apiResponse->response());
        
        // Another way to get message, but keep in mind, that there could be no response if request has failed completely
        // print '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        $message = '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // craft a friendly message here.
        $return_message = "There was an error adding you to our SMS list, Please try again later <br/>" . $message;
    }
} // end send_welcome_mobile function

/* ============================================== */
/* generate unique ID for new subscriber function */
/* ============================================== */
function unique_token() {
    global $wpdb;
    $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `token_prefix`
            FROM `ringcentral_control` WHERE `ringcentral_control_id` = %d", 1 )
        );
    $prefix = $result_rc->token_prefix ;
    return uniqid($prefix, true) ;
}
/* ======================================== */
/* get from phone number from control table */
/* it is stored in the user_name field      */
/* ======================================== */
function ringcentral_get_from() {
    global $wpdb;
    $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_user_name`
            FROM `ringcentral_control` WHERE `ringcentral_control_id` = %d", 1 )
        );
    return $result_rc->ringcentral_user_name ;
}
/* ========================= */
/* call ringout api function */
/* ========================= */
function ringcentral_ringout($to) {
    $sdk = ringcentral_sdk() ;
    $from = ringcentral_get_from();
    try {
        $apiResponse = $sdk->platform()->post('/account/~/extension/~/ringout',
            array(
                // dynamic eventually
                'from' => array('phoneNumber' => $from),
                // number from the widget form
                'to'   =>  array('phoneNumber' => $to) )
            );
    } catch (\RingCentral\SDK\Http\ApiException $e) {
        
        // Getting error messages using PHP native interface
        //                     print 'Expected HTTP Error: ' . $e->getMessage() . PHP_EOL;
        
        // In order to get Request and Response used to perform transaction:
        $apiResponse = $e->apiResponse();
        //                     print_r($apiResponse->request());
        //                     print_r($apiResponse->response());
        
        // Another way to get message, but keep in mind, that there could be no response if request has failed completely
        // print '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // $message = '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // craft a friendly message here.
        // $return_message = "There was an error adding you to our SMS list, please contact us or try again later";
    }
}

/* ============================================================ */
/* Validate RingCental SDK connection with provided credentials */
/* ============================================================ */
function ringcentral_validate_sdk($rc_handshake) {
    // Include Libraries
    require('vendor/autoload.php');
    
    // Setup Client
    $sdk = new RingCentral\SDK\SDK($rc_handshake['client_id'], $rc_handshake['client_secret'], RingCentral\SDK\SDK::SERVER_SANDBOX);
    
    // attempt to Login via API
    try {
        $sdk->platform()->login($rc_handshake['user_name'], $rc_handshake['extension'], $rc_handshake['password']);
        $result = true ;
    } catch (\RingCentral\SDK\Http\ApiException $e) {
        $result = false ;
    }
    return $result ;
}

/* ============================== */
/* Build help icon and title text */
/* ============================== */
function build_help($field) {
    global $wpdb;
    $image_source = plugin_dir_url(__FILE__) . '../images/question_mark.png' ;
    $result_rc_help = $wpdb->get_row( $wpdb->prepare("SELECT ringcentral_help_help AS help_text
            FROM `ringcentral_help` WHERE `ringcentral_help_field` = %s", $field) );

    $out_string = "<img src='$image_source' title='$result_rc_help->help_text' />" ;
    return $out_string ;
}
?>