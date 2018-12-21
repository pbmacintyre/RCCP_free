<?php 
/* ====================================== */
/* bring in generic ringcentral functions */
/* ====================================== */

error_reporting(E_ALL & ~E_NOTICE);
ini_set('display_errors', 1);

require( '../../../../../wp-load.php' );

global $wpdb;

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

    echo "<pre>";
    var_dump($result_rc) ;
    echo "</pre>";

// Login via API
if (!$sdk->platform()->loggedIn()) {
    $sdk->platform()->login($ringcentral_user_name, $ringcentral_extension, $ringcentral_password);
}
    
echo "Here ... <br/>";

$result_rc = $wpdb->get_row( $wpdb->prepare("SELECT oauth_client, oauth_secret FROM `ringcentral_control`
        WHERE `ringcentral_control_id` = %d", 1)
    );
$oauth_client = $result_rc->oauth_client ;
$oauth_secret = $result_rc->oauth_secret ;

// try {
//     $apiResponse = $sdk->platform()->post('/oauth/token'
//     //          /restapi/v1.0/account/{accountId}/extension/{extensionId}/ring-out
//     //             $url = "https://platform.devtest.ringcentral.com/restapi/oauth/token" ;
        
//     //             restapi/oauth/token
//         );
//     echo "<pre>";
//     var_dump($apiResponse) ;
//     echo "</pre>";
    
// } catch (\RingCentral\SDK\Http\ApiException $e) {
    
//     // Getting error messages using PHP native interface
//     print 'Expected HTTP Error: ' . $e->getMessage() . PHP_EOL;
    
//     // In order to get Request and Response used to perform transaction:
//     //         $apiResponse = $e->apiResponse();
//     print_r($apiResponse->request());
//     print_r($apiResponse->response());
    
// }

?>