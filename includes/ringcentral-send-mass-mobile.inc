<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

$website_name = get_bloginfo('name') ;

$mobile_list = $wpdb->get_results( $wpdb->prepare("SELECT `ringcentral_token`, `full_name`, `mobile`
    FROM `ringcentral_contacts` WHERE `mobile` <> %s AND `mobile_confirmed` = %d", "", 1 ) ); 

$sdk = ringcentral_sdk() ;

$from = ringcentral_get_from();

foreach ( $mobile_list as $mobile_contact ) {	
	$unsub_url = add_query_arg(array('rcunsubscribe'=>$mobile_contact->ringcentral_token, 'rcformat'=>'2'), get_site_url());
    
    $message = "hi $mobile_contact->full_name : A new post has been added to:  $website_name \n\n";
    $message .= $post->post_title . ": " . $post_url . "\n\n";
    $message .= "To unsubscribe follow this link: " ;
    $message .= "$unsub_url ";
    
    try {
        $apiResponse = $sdk->platform()->post('/account/~/extension/~/sms',
            array('from' => array('phoneNumber' => $from),
                'to'   => array( array('phoneNumber' => $mobile_contact->mobile) ),
                'text' => $message ) );
        
//         $wpdb->query( $wpdb->prepare("INSERT INTO `a_dumps` (`dump_content`)
//         VALUES (%s)", serialize($apiResponse) ) );
        
    } catch (\RingCentral\SDK\Http\ApiException $e) {
        
        // In order to get Request and Response used to perform transaction:
        $apiResponse = $e->apiResponse();

//         $wpdb->query( $wpdb->prepare("INSERT INTO `a_dumps` (`dump_content`) 
//             VALUES (%s)", serialize($apiResponse) ) );
        
        // Another way to get message, but keep in mind, that there could be no response if request has failed completely
        // print '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // $message = '  Message: ' . $e->apiResponse->response()->error() . PHP_EOL;
        // craft a friendly message here.
        $return_message = "There was an error broadcasting to the mobile list => " . $apiResponse;
    }
	// Sleep for 1.8 seconds to prevent 40/min penalty
	usleep(1800000);
}
?>