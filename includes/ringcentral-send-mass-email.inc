<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

/* if you want to let the admins know of an email distribution */
/* activate this code and update the to email address -- start */

// $subject = 'admin - A post has been updated';

// $message = "Hi Admin: A post has been added on your website:\n\n";
// $message .= $post->post_title . ": " . $post_url;

// // Send email to admin.
// wp_mail( 'pbmacintyre@gmail.com', $subject, $message );
/* activate this code -- end */

// now send email(s) to signed up client(s)

$email_list = $wpdb->get_results( $wpdb->prepare("SELECT `ringcentral_token`, `full_name`, `email`
    FROM `ringcentral_contacts` WHERE `email` <> %s AND `email_confirmed` = %d", "", 1 ) );  

// should there be some kind of batch process to send out only 50 emails at a time or something so that 
// we are not marked as spammers ?  If so, how would we do that?
foreach ( $email_list as $email_contact ) {
	$unsub_url = add_query_arg(array('rcunsubscribe'=>$mobile_contact->ringcentral_token, 'rcformat'=>'1'), get_site_url());
    
    $subject = 'A new post has been added to: ' . $siteName;
    
    $message = "hi $email_contact->full_name : A new post has been added to:  $siteName <br/>";
    $message .= "email: $email_contact->email <br/>";
    $message .= $postTitle . ": " . $postUrl;
    $message .= "<br/><br/><br/><br/>To unsubscribe click here: " ;
    $message .= "<a href='" . $unsub_url . "'>Unsubscribe eMail</a>";
    
    $recipient = '"' . $email_contact->full_name . '" <' . $email_contact->email . '>' ;
    $headers = array('Content-Type: text/html; charset=UTF-8');
    wp_mail( $recipient, $subject, $message, $headers );
}
?>