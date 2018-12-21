<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

$website_name = get_bloginfo('name') ;

$post_url = get_permalink( $post->ID );

/* if you want to let the admins know of an email distribution */
/* activate this code and update the to email address -- start */

// $subject = 'admin - A post has been updated';

// $message = "Hi Admin: A post has been added on your website:\n\n";
// $message .= $post->post_title . ": " . $post_url;

// // Send email to admin.
// wp_mail( 'pbmacintyre@gmail.com', $subject, $message );
/* activate this code -- end */

// now send email(s) to signed up client(s)

$email_list = $wpdb->get_results( $wpdb->prepare("SELECT `ringcentral_contacts_id`, `full_name`
    FROM `ringcentral_contacts`
    WHERE `email` <> %s AND `email_confirmed` = %d",
    "", 1 )
    );  

// should there be some kind of batch process to send out only 50 emails at a time or something so that 
// we are not marked as spammers ?  If so, how would we do that?
foreach ( $email_list as $email_contact ) {
    $unsub_url = plugins_url('/', __FILE__) . "ringcentral-unsubscribe.php?contact_id=" . $email_contact['ringcentral_contacts_id'];
    $unsub_url .= "&method=1" ;
    
    $subject = 'A new post has been added to: ' . $website_name;
    
    $message = "hi $email_contact[full_name] : A new post has been added to:  $website_name <br/>";
    $message .= "email: $email_contact[email] <br/>";
    $message .= $post->post_title . ": " . $post_url;
    $message .= "<br/><br/><br/><br/>To unsubscribe click here: " ;
    $message .= "<a href='" . $unsub_url . "'>Unsubscribe eMail</a>";
    
    $recipient = '"' . $email_contact['full_name'] . '" <' . $email_contact['email'] . '>' ;
    $headers = array('Content-Type: text/html; charset=UTF-8');
    wp_mail( $recipient, $subject, $message, $headers );
}
?>