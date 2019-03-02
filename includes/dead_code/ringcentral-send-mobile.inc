<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */
error_reporting(E_ALL);
ini_set('display_errors', 0);

$website_name = get_bloginfo('name') ;

$mobile_list = $wpdb->get_results( $wpdb->prepare("SELECT `ringcentral_contacts_id`, `full_name`
    FROM `ringcentral_contacts`
    WHERE `mobile` <> %s AND `mobile_confirmed` = %d",
    "", 1 )
    ); 

$sdk = ringcentral_sdk() ;

foreach ( $mobile_list as $mobile_contact ) {
    $unsub_url = plugins_url('/', __FILE__) . "ringcentral-unsubscribe.php?contact_id=" . $mobile_contact['ringcentral_contacts_id'];
    $unsub_url .= "&method=2" ;
    
    $message = "hi $mobile_contact[full_name] : A new post has been added to:  $website_name \n\n";
    $message .= $post->post_title . ": " . $post_url . "\n\n";
    $message .= "To unsubscribe follow this link: " ;
    $message .= "$unsub_url ";
    
    try {
        $apiResponse = $sdk->platform()->post('/account/~/extension/~/sms',
            array('from' => array('phoneNumber' => '+13128589779'),
                'to'   => array( array('phoneNumber' => $mobile_contact['mobile']) ),
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
        $return_message = "There was an error broadcasting to the mobile list.";
    }
}
?>