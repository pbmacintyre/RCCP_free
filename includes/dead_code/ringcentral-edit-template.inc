<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "green") {	
	global $print_again, $wpdb;	?>		
	<form action="" method="post" >	
	<?php $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `ringcentral_templates`
        WHERE `ringcentral_template_id` = %d", $_GET['id'])
	    ); 
	$template_type = $result_rc->template_type ;
	?>
	<input type="hidden" name="rc_template_id" value="<?php echo $_GET['id'] ; ?>" >
	<input type="hidden" name="rc_template_type" value="<?php echo $template_type ; ?>" >
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
	if ($print_again == true) {
		echo "<font color='$color'><strong>" . $message . "</strong></font>";
	} else {
	    echo "<font color='$color'><strong>" . $message . "</strong></font>";
	}
	?></td>
	</tr>	
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline;' >Template Name:</p>			
		</td>
		<td class="right_col">
			<?php echo $result_rc->template_name ; ?>
		</td>
	</tr>	
	<?php if ($template_type == "Email") {   ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "subject") echo "color:red"; ?>' >Tempalte Subject:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="subject" value="<?php 
		  if ($print_again) {
		      echo $_POST['subject'];
          } else {             
              if ($result_rc->subject) {
                  echo $result_rc->subject ;
              } 
          }
            ?>"></td>
	</tr>	
	<?php } ?>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "body") echo "color:red"; ?>' >Template Body:</p>
			<p style='color: red; display: inline'>*</p>
			<p style='color: red; '>Personalize the template with {{full_name}}</p>
		</td>
		<td class="right_col">		
		<?php 
		if ($print_again) {
		    $body_content = $_POST['body'];
		} else {
		    if ($result_rc->body) {
		        $body_content = $result_rc->body ;
		    } else {
		        $body_content = "" ;
		    }
		}		
		$settings = "";
		wp_editor( $body_content, "body", $settings) ; 
		
		if ($result_rc->template_name == "Opt-in Email") {   ?>
            <strong>NOTE:</strong> This will be added to the end of each Opt-in email:
            <p><strong>[If this was not you please ignore this email]</strong>
			If you also signed up for SMS messaging you will receive a separate confirmation text in that regard.
			Please follow this link to confirm your subscription to our email notification list: 
            [link provided at email generation time]</p>
            <?php } ?>
            
            <?php if ($result_rc->template_name == "Opt-in SMS") {   ?>
            <strong>NOTE:</strong> This will be added to the end of each Opt-in Text Message:
            <p><strong>[If this was not you please ignore this message]</strong>			
    		If you also signed up for email notifications you will receive a separate confirmation email in that regard.
    		Please follow this link to confirm your SMS subscription to our mailing list: 
            [link provided at SMS generation time]</p>
            <?php } ?>
            
            <?php if ($result_rc->template_name == "New Blog Post Email") {   ?>
            <strong>NOTE:</strong> The following will be added to the end of each Blog Post notification email:
            <p>The new post's title with link to the post and an unscubscription option link</p>
            <?php } ?>
            
            <?php if ($result_rc->template_name == "New Blog Post SMS") {   ?>
            <strong>NOTE:</strong> The following will be added to the end of each Blog Post notification text:
            <p>The new post's title with link to the post and an unscubscription option link</p>
            <?php } ?>
                           
            </td>
	</tr>		
	<?php /* ============================================== */ ?>	
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$other_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Template","","submit","",$other_attributes); ?>
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
	
	/* data integrity checks */	
	if ($_POST['subject'] == "" && $_POST['rc_template_type'] == "Email" ) {
	    $print_again = true;
	    $label = "subject";
	    $error = "<b>Template subject cannot be blank.</b>";
	}	
	if ($_POST['body'] == "") {
	    $print_again = true;
	    $label = "body";
	    $error = "<b>Template body cannot be blank.</b>";
	}
	// end data integrity checking
	
	if ($print_again == true) {
	    $color = "red";
	    show_form($error, $label, $color);
	} else {	    
	    /* convert and / or sanitize any needed form POST values */
	    
// 	    if ($_POST['embedded_phone'] == "on") { 
// 	        $embedded_phone = 1;	        
//         } else {
//             $embedded_phone = 0;
//         }
            
        $rc_template_id = $_POST['rc_template_id'] ;
        $subject        = $_POST['subject'] ;
        $body           = $_POST['body'] ; 
	    
        $wpdb->query( $wpdb->prepare("UPDATE `ringcentral_templates` SET
            `subject` = %s, `body` = %s WHERE `ringcentral_template_id` = %d",
            $subject, $body, $rc_template_id)
            );

        $color = "red";
	    show_form("Configuration Changes have been saved",'',$color) ;	       
	}
}

/* ============= */
/*  --- MAIN --- */
/* ============= */
if(isset($_POST['submit'])) {
	check_form();
} else {
	$message = "Adjust settings to your preferences";
	show_form($message);
} 
?>