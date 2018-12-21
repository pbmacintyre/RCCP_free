<?php 

$sdk = ringcentral_sdk() ;

$response = $platform->post('/account/~/extension/~/ringout', array(
    'from' => array('phoneNumber' => '+18084652470'),
    'to'   => array('phoneNumber' => $_GET['phone_to'])
));
$json = $response->json();
$lastStatus = $json->status->callStatus;
// Poll for call status updates
while ($lastStatus == 'InProgress') {
    $current = $platform->get($json->uri);
    $currentJson = $current->json();
    $lastStatus = $currentJson->status->callStatus;
    print 'Status: ' . json_encode($currentJson->status) . PHP_EOL;
    sleep(2);
}
?>