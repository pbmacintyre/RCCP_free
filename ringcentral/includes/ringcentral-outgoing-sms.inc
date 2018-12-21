<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */
error_reporting(E_ALL);
ini_set('display_errors', 1);

/* ================================= */
/* Bootstrap code begins             */
/* ================================= */

// require_once(__DIR__ . '/../vendor/autoload.php');

use RingAPI\SDK\Http\ApiException;

date_default_timezone_set('UTC');

// Make all PHP errors to be thrown as Exceptions

set_error_handler(function ($errno, $errstr, $errfile, $errline) {
    if (!(error_reporting() & $errno)) {
        return;
    }
    throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
});
    
// Set up global exception handler (this includes Guzzle HTTP Exceptions)

set_exception_handler( function (Exception $e) {
    
    print 'Exception: ' . $e->getMessage() . PHP_EOL;
    
    if ($e instanceof ApiException) {
        
        print 'SDK HTTP Error at ' . $e->apiResponse()->request()->getUri() . PHP_EOL .
        'Response text: ' . $e->apiResponse()->text() . PHP_EOL;
        
    }
    
    if ($e->getPrevious()) {
        print 'Previous: ' . $e->getPrevious()->getMessage() . PHP_EOL;
    }
    
    print $e->getTraceAsString() . PHP_EOL;
    
} ) ;  //end set_excepption code
    
/* ================================= */
/* Bootstrap code ends               */ 
/* ================================= */
    
use RingCentral\SDK\SDK;

// Create SDK instance

$credentials = require('ringcentral-credentials.php');

$rcsdk = new SDK($credentials['clientId'], $credentials['clientSecret'], $credentials['server'], 'Demo', '1.0.0');

$platform = $rcsdk->platform();

// Authorize

$platform->login($credentials['username'], $credentials['extension'], $credentials['password']);

// Find SMS-enabled phone number that belongs to extension

$phoneNumbers = $platform->get('/account/~/extension/~/phone-number', array('perPage' => 'max'))->json()->records;

$smsNumber = null;

foreach ($phoneNumbers as $phoneNumber) {

    if (in_array('SmsSender', $phoneNumber->features)) {

        $smsNumber = $phoneNumber->phoneNumber;

        break;

    }

}

print 'SMS Phone Number: ' . $smsNumber . PHP_EOL;

// Send SMS

if ($smsNumber) {

    $response = $platform
        ->post('/account/~/extension/~/sms', array(
            'from' => array('phoneNumber' => $smsNumber),
            'to'   => array(
                array('phoneNumber' => $credentials['mobileNumber']),
            ),
            'text' => 'Test from PHP',
        ));

    print 'Sent SMS ' . $response->json()->uri . PHP_EOL;

} else {

    print 'SMS cannot be sent: no SMS-enabled phone number found...' . PHP_EOL;

}

