<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Get Validation Token
$v_Token = isset($_SERVER['HTTP_VALIDATION_TOKEN']) ? $_SERVER['HTTP_VALIDATION_TOKEN'] : '' ;

// return validation Token as a header
if (strlen($v_Token) > 0) {
    header("Validation-Token: {$v_Token}");
}

/*
POST https://platform.devtest.ringcentral.com/restapi/v1.0/subscription

Authorization: Bearer %YOUR_OAUTH_GENERATED_TOKEN%
Content-Type: application/json

{
    "eventFilters": ["/restapi/v1.0/account/~/extension/~/message-store"],
    "deliveryMode": {
    "transportType": "WebHook",
    "address": "https://puns.theapi.ninja/incoming.php",
    "encryption": true
},
"expiresIn": 604800
} */

?>