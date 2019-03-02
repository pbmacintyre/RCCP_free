<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

/* ================================= */
/* Bootstrap code begins             */
/* ================================= */
global $wpdb;

$website_name = get_bloginfo('name') ;

$email_sql = "SELECT `ringcentral_contacts_id`,`full_name`,`mobile` FROM `ringcentral_contacts` "; 
$email_sql .= "WHERE `mobile` <> '' AND `mobile_confirmed` = 1 ";
$email_list = $wpdb->get_results($email_sql, ARRAY_A);

$sdk = ringcentral_sdk() ;

foreach ( $email_list as $email_contact ) {
    $unsub_url = plugins_url('/', __FILE__) . "ringcentral-unsubscribe.php?contact_id=" . $email_contact['ringcentral_contacts_id'];
    $unsub_url .= "&method=2" ;
    
    $message = "hi $email_contact[full_name] : A new post has been added to:  $website_name \n\n";
    $message .= $post->post_title . ": " . $post_url . "\n\n";
    $message .= "To unsubscribe follow this link: " ;
    $message .= "$unsub_url ";
    
    try {
        $apiResponse = $sdk->platform()->post('/account/~/extension/~/sms',
            array('from' => array('phoneNumber' => '+13128589779'),
                'to'   => array( array('phoneNumber' => $email_contact['mobile']) ),
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
        // $message = '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // craft a friendly message here.
        $return_message = "There was an error broadcasting to the SMS list.";
    }
}