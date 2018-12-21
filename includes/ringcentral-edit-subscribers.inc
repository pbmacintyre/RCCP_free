<?php
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "green") {
	global $print_again, $wpdb;  
	
	$ringcentral_contacts_id = $_GET['id'] ;
	?>
	<form action="" method="post" >
	<input type="hidden" name="rc_contact_id" value="<?php echo $ringcentral_contacts_id ;?>" >
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
    $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `ringcentral_contacts`
        WHERE `ringcentral_contacts_id` = %d", $ringcentral_contacts_id)
    );

	if ($print_again == true) {
		echo "<font color='$color'><strong>" . $message . "</strong></font>";
	} else {
	    echo "<font color='$color'><strong>" . $message . "</strong></font>";
	}	
	?></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "full_name") echo "color:red"; ?>' >Full Name:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col">
			<input type="text" name="full_name" 
			value="<?php if ($print_again) { 
			    echo $_POST['full_name']; 
			} else {
			    echo $result_rc->full_name ;
            }?>">
		</td>
	</tr>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "email") echo "color:red"; ?>' >email:</p>			
		</td>
		<td class="right_col">
			<input type="text" name="email" 
			value="<?php if ($print_again) { 
			    echo $_POST['email']; 
			} else {
			    echo $result_rc->email ;
            }?>">
		</td>
	</tr>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "mobile") echo "color:red"; ?>' >mobile:</p>			
		</td>
		<td class="right_col">
			<input type="text" name="mobile" onkeypress="return isNumberKey(event)" 
			value="<?php if ($print_again) { 
			    echo $_POST['mobile']; 
			} else {
			    echo $result_rc->mobile ;
            }?>">
		</td>
	</tr>
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$other_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","submit","",$other_attributes); ?>
			<br/><br/>
		</td>
	</tr>
	</table>
	</form>
<?php
}
/* ========== */
/* check_form */
/* ========== */
Function check_form() {
	
	global $print_again, $wpdb;
	
	$rc_contact_id = $_POST['rc_contact_id'] ;
	$full_name     = $_POST['full_name'] ;
	$email         = $_POST['email'] ;
	$mobile        = $_POST['mobile'] ;	
	
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
        $return_message = "eMail and Mobile cannot both be blank.";
    }
    if ($email !== "" && filter_var($email, FILTER_VALIDATE_EMAIL) == FALSE){
        $print_again = true;
        $label = "email";
        $return_message = "eMail is malformed";
    }
    if ($mobile != "" && strlen($mobile) !== 10) {
        $print_again = true;
        $label = "mobile";
        $return_message = "Mobile number must be 10 digits";
    }
    if ($full_name == "") { 
        $print_again = true;
        $label = "full_name";
        $return_message = "Full Name cannot be blank."; 
    }    
    /* ========================= */
    /* end data integrity checks */
    /* ========================= */	
    
//     echo "</br> Trimmed mobile: [" . $mobile ."]";
    
	if ($print_again == true) {
	    show_form($return_message, $label, 'red');
	} else {	    
	    /* ========================== */
	    /* prep for saving the data   */
	    /* ========================== */
	    // add the country code prefix
	    if ($mobile != "" ) $mobile = "+1" . $mobile ; 
	    
	    // if only given an email, check to see if we already have it
	    if ($email != "" && $mobile == "") {
	        $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id`
                FROM `ringcentral_contacts` WHERE `email` = %s", $email )
	        );
	        if ($result_rc->ringcentral_contacts_id) {
	            $return_message = "<center>That email is already on file.</center>" ;
	        } else {
	            // update record
	            $wpdb->query( $wpdb->prepare("UPDATE `ringcentral_contacts` SET `email` = '%s'
                    WHERE `ringcentral_contacts` = %d",
                    $email, $rc_contact_id )
	            );
	            $return_message = "<center>Contact Information updated...</center>" ;
	        }
	    }
	    // if only given an mobile, check to see if we already have it
	    if ($email == "" && $mobile != "") {
	        $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id`
                FROM `ringcentral_contacts` WHERE `mobile` = %s", $mobile )
            );
	        if ($result_rc->ringcentral_contacts_id) {
	            $return_message = "<center>That mobile number is already on file.</center>" ;
	        } else {
	            // update record
	            $wpdb->query( $wpdb->prepare("UPDATE `ringcentral_contacts` SET `mobile` = '%s'
                    WHERE `ringcentral_contacts` = %d",
                    $mobile, $rc_contact_id )
	            );
	            $return_message = "<center>Contact Information updated...</center>" ;
	        }
	    }
	    // if given both an email and mobile, check to see if we already have them
	    if ($email != "" && $mobile != "") {
	        // Check to see if we already have both email and mobile on file.
	        $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_contacts_id`
                FROM `ringcentral_contacts` WHERE `email` = %s OR `mobile` = %s",
                $email, $mobile )
	        );
	        if ($result_rc->ringcentral_contacts_id) {
	            $return_message = "<center>Contact Information already on file...</center>" ;
	        } else { // save new data
	            // update record
	            $wpdb->query( $wpdb->prepare("UPDATE `ringcentral_contacts` 
                    SET `email` = '%s', `mobile` = '%s'
                    WHERE `ringcentral_contacts` = %d",
                    $email, $mobile, $rc_contact_id )
	            );
	            $return_message = "<center>Contact Information updated...</center>" ;
	        }
	    }  //end if already exists test
	    $color = "red";	    
	    show_form($return_message,'',$color) ;	
	}	    
}
/* ============= */
/*  --- MAIN --- */
/* ============= */
if(isset($_POST['submit'])) {
	check_form();
} else {
	$message = "Edit this subscriber's data";
	show_form($message);
} 
?>