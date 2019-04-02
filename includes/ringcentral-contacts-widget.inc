<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */
class ringcentral_contacts_widget extends WP_Widget {
    // instantiate the class
    function ringcentral_contacts_widget() {
        $widget_ops = array(
          'classname' => 'ring_central_contacts_widget_class',
          'description' => 'When signing up for new Post Notifications also offer SMS messages.'
        );
        $this->WP_Widget(
            'ring_central_contacts_widget',
            'RCCP-Free Contacts Widget',
            $widget_ops );
    }
    
    // build the widget settings form
    function form($instance) {
        $defaults = array('title' => 'News Feed Sign Up' );
        $instance = wp_parse_args( (array) $instance, $defaults );
        $title = $instance['title'];    ?>
        <p>Title: <input type="text" class="widefat"
        	name="<?php echo $this->get_field_name( 'title' ); ?>" 
        	value="<?php echo esc_attr($title) ; ?>" /></p>      
<?php }
    // save widget settings function on admin widget
    function update($new_instance, $old_instance) {
        $instance = $old_instance ;
        $instance['title'] = strip_tags($new_instance['title']) ;
        return $instance ;        
    }
    
    // display the widget
    function widget ($args, $instance) {
        global $wpdb ;
        
        extract($args);
        echo $before_widget;
        $title = apply_filters ('widget_title', $instance['title']);        
        if (!empty($title) ) { echo $before_title . $title . $after_title; } ;

//         echo $_POST["widget-ring_central_contacts_widget"][2]['full_name'] ;       
        ?>
        <form action="" method="post" >        		
        <p> Full Name: <input type="text" class="widefat" name="full_name" value="" /></p>
                                
        <p> eMail: <input type="text" class="widefat" name="email" value="" /></p>
            
        <p> Mobile #: <input type="text" class="widefat" name="mobile" value="" onkeypress="return isNumberKey(event)" /></p>
                         
		<br/><br/>
		<center>
		<input type="submit" name="submit" value="Join List" style="background: #008ec2; border-color: #006799; color: #fff;">
		</center>
        </form>
<?php           
        // check that the form was submitted
        if(isset($_POST['submit']) && $_POST['submit'] == "Join List" ) {
            echo $this->public_save($_POST);
        }
        
        echo $after_widget ;  
    }
    /* ===================== */
    /* save public form data */
    /* ===================== */
    function public_save($FormData) {
        global $wpdb;
        $contacts_widget_return_message = "";
        
        $full_name  = $FormData['full_name'] ;
        $email      = $FormData['email'] ;
        $mobile     = $FormData['mobile'] ;  
                        
        /* =================================== */
        /* data integrity checks, data massage */
        /* =================================== */        
    	// only take the mobile numbers
    	$mobile = preg_replace("/[^0-9]/", '', $mobile);
    	// remove leading digit if it is a 1
    	if (substr($mobile, 0, 1) == "1") { $mobile = substr($mobile, 1) ; }
    	
        if ($email == "" && $mobile == "") {        
            $print_again = true;
            $label = "email";
            $contacts_widget_return_message = "eMail and Mobile cannot both be blank.";
        }
        if ($email !== "" && filter_var($email, FILTER_VALIDATE_EMAIL) == FALSE){
            $print_again = true;
            $label = "email";
            $contacts_widget_return_message = "eMail is malformed";
        }
        if ($mobile != "" && strlen($mobile) !== 10) {
            $print_again = true;
            $label = "mobile";
            $contacts_widget_return_message = "Mobile number must be 10 digits";
        }
        if ($full_name == "") { 
            $print_again = true;
            $label = "full_name";
            $contacts_widget_return_message = "Full Name cannot be blank."; 
        }    
        /* ========================= */
        /* end data integrity checks */
        /* ========================= */	
        if (!$print_again) {
            
            /* ======================== */
            /* prep for saving the data */
            /* ======================== */
            // add the country code prefix
            if ($mobile != "" ) $mobile = "+1" . $mobile ; 
            
            // generate unique token with control prefix.
            $uniq_token = unique_token() ;
            
            // if only given an email, check to see if we already have it
            if ($email != "" && $mobile == "") {                
                $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id` 
                    FROM `ringcentral_contacts`
                    WHERE `email` = %s",
                    $email )
                    );       
                if ($result_rc->ringcentral_contacts_id) {
                    $contacts_widget_return_message = "<br/><center>That email is already on file.<br/>Thanks for previously joining us!</center>" ;              
                } else {
                    // save with name
                    $wpdb->query( $wpdb->prepare("INSERT INTO 
                        `ringcentral_contacts` (`ringcentral_token`, `full_name`, `email`) 
                        VALUES (%s, %s, %s )",
                        $uniq_token, $full_name, $email ) 
                    );            
                    send_welcome_email($email, $uniq_token, $full_name );                   
                    $contacts_widget_return_message = "<br/><center><font color='green'>Contact Information saved...<br/>Check your email to confirm<br/>Thanks for joining us!</font></center>" ;                    
                }
            }
            // if only given an mobile, check to see if we already have it
            if ($email == "" && $mobile != "") {                
                $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id`
                    FROM `ringcentral_contacts`
                    WHERE `mobile` = %s",
                    $mobile )
                    );                
                if ($result_rc->ringcentral_contacts_id) {
                    $contacts_widget_return_message = "<br/><center>That mobile number is already on file.<br/>Thanks for previously joining us!</center>" ;
                } else {
                    // save with name
                    $wpdb->query( $wpdb->prepare("INSERT INTO
                        `ringcentral_contacts` (`ringcentral_token`,`full_name`, `mobile`)
                        VALUES (%s, %s, %s )",
                        $uniq_token, $full_name, $mobile )
                    );
                    send_welcome_mobile($mobile, $uniq_token, $full_name) ;
                    $contacts_widget_return_message = "<br/><center><font color='green'>Contact Information saved...<br/>Check your phone to confirm<br/>Thanks for joining us!</font></center>" ;                   
                }
            }            
            // if given both an email and mobile, check to see if we already have them
            if ($email != "" && $mobile != "") {             
                // Check to see if we already have both email and mobile on file.               
                $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id`
                    FROM `ringcentral_contacts`
                    WHERE `email` = %s OR `mobile` = %s",
                    $email, $mobile )
                );
                if ($result_rc->ringcentral_contacts_id) {
                    $contacts_widget_return_message = "<br/><center>Contact Information already on file...<br/>Thanks for previously joining us!</center>" ;                   
                } else { // save new data
                    $wpdb->query( $wpdb->prepare("INSERT INTO
                        `ringcentral_contacts` (`ringcentral_token`, `full_name`, `email`, `mobile`)
                        VALUES (%s, %s, %s, %s )",
                        $uniq_token, $full_name, $email, $mobile )
                    );                    
                    // send both welcome output
                    send_welcome_email($email, $uniq_token, $full_name );
                    send_welcome_mobile($mobile, $uniq_token, $full_name) ;
                    $contacts_widget_return_message = "<br/><center><font color='green'>Contact Information saved...<br/>Check your email/phone to confirm<br/>Thanks for joining us!</font></center>" ;                    
                }
            }  //end if already exists test        
        } else {
            // end data intergity fail tests
            $contacts_widget_return_message = "<br/><center><font color='red'>" . $contacts_widget_return_message . "</font></center>";            
        }
        
        // show message on widget area
        return $contacts_widget_return_message ;
    } // end public_save method
    
} // end of class definition
?>