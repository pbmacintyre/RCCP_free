<?php
/**
 * Copyright (C) 2019-2021 Paladin Business Solutions
 *
 */

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "#008EC2") {	
	
	global $print_again, $wpdb;    	
	
	if (ringcentral_CheckPro()) { ?>
        <form action="<?php echo RINGCENTRAL_PRO_URL ?>" target="_blank" style="padding-left: 15%;">
            <?php 
            $btn_attributes = array( "style" => "background: red; border-color: #006799; color: #fff;" ); 
            submit_button("Get Pro Version","","submit","",$btn_attributes);
            ?>        
        </form>
    <?php } ?>

	<?php if (empty($_SERVER['HTTPS']) || $_SERVER['HTTPS'] == 'off') { ?>
	<div style="margin-top: 5px; width: 93%; max-width: 786px; border: 1px solid #900; padding: 10px; background: #ffe6e6; font-weight: bold; text-align: center;">
		To comply with CTIA guidelines, please enable HTTPS and save your settings<br />(this will allow for your users to opt out with the STOP keyword).
	</div>	
	<?php } ?>

	<form action="" method="post" >
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
	if ($print_again == true) {
		echo "<font color='$color'><strong>" . esc_html($message) . "</strong></font>";
	} else {
	    echo "<font color='$color'><strong>" . esc_html($message) . "</strong></font>";	    
	}
	
	$result_rc = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `ringcentral_control` WHERE `ringcentral_control_id` = %d", 1) );
	
	?></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "embedded_phone") echo "color:red"; ?>' >Use Embedded Phone?</p>
			
			<?php echo ringcentral_build_help("embedded_phone") ; ?>
						
		</td>
		<td class="right_col"><input type="checkbox" name="embedded_phone" <?php 
		if ($print_again) { 
		    if ($_POST['embedded_phone'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc->embedded_phone == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "email_updates") echo "color:red"; ?>' >Send Post Updates by eMail?</p>			
		</td>
		<td class="right_col"><input type="checkbox" name="email_updates" <?php 
		if ($print_again) { 
		    if ($_POST['email_updates'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc->email_updates == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>    
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "mobile_updates") echo "color:red"; ?>' >Send Post Updates over SMS Text?</p>			
		</td>
		<td class="right_col"><input type="checkbox" name="mobile_updates" <?php 
		if ($print_again) { 
		    if ($_POST['mobile_updates'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc->mobile_updates == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>
    
    <tr class="TableOverride">
        <td class="left_col">
            <p style='display: inline; <?php if ($label == "ringcentral_sandbox") echo "color:red"; ?>' >Use the RingCentral SANDBOX SDK?</p>  
            
            <?php echo ringcentral_build_help("ringcentral_sandbox") ; ?>
                      
        </td>
        <td class="right_col"><input type="checkbox" name="ringcentral_sandbox" <?php 
        if ($print_again) { 
            if ($_POST['ringcentral_sandbox'] == "on") {
              echo 'CHECKED';
            } 
          } else {             
              if ($result_rc->ringcentral_sandbox  == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
    </tr>
	<?php /* ==============================================  ?>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "oauth_client") echo "color:red"; ?>' >OAuth Client Key:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="oauth_client" value="<?php 
		  if ($print_again) {
		      echo $_POST['oauth_client'];
          } else {             
              if ($result_rc->oauth_client) {
                echo $result_rc->oauth_client ;
              } else {
                echo "&nbsp; test " ;  
              }
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "oauth_secret") echo "color:red"; ?>' >OAuth Secret Key:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="password" name="oauth_secret" value="<?php 
		  if ($print_again) {
		      echo $_POST['oauth_secret'];
          } else {             
              if ($result_rc->oauth_secret) {
                  echo $result_rc->oauth_secret ;
              } else {
                  echo "&nbsp;" ;
              } 
          }
            ?>"></td>
	</tr>	
	<?php /* ============================================== */ ?>
    <tr>
        <td colspan=2>
        	<hr>
        </td>
    </tr>	
	<?php /* ============================================== */ ?>
	<tr class="TableOverride">
        <td class="left_col">
            <p style='display: inline;' >Reveal Passwords:</p>
        </td>
        <td class="right_col">             
            <button type="button" onmouseout="hide_it();" onmousedown="reveal_it();" onmouseup="hide_it();">Toggle Passwords</button>     
        </td>
    </tr>   
    <tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "client_id") echo "color:red"; ?>' >Client ID:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="client_id" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['client_id']);
          } else {             
              if ($result_rc->client_id) {
                  echo $result_rc->client_id ;
              } else {
                echo "&nbsp;" ;  
              }
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "client_secret") echo "color:red"; ?>' >Client Secret Key:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="password" name="client_secret" id="myClientSecret" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['client_secret']);
          } else {             
              if ($result_rc->client_secret) {
                echo $result_rc->client_secret ;
              } 
          }
            ?>" > 
            </td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col" valign="top">
		<p style='display: inline; <?php if ($label == "ringcentral_user_name") echo "color:red"; ?>' >RingCentral Number:</p>
		<p style='color: red; display: inline'>*</p>
        
        <?php echo ringcentral_build_help("username") ; ?>
              
		</td>
		<td class="right_col" valign="top"><input type="text" name="ringcentral_user_name" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['ringcentral_user_name']);
          } else {             
              if ($result_rc->ringcentral_user_name) {
                echo $result_rc->ringcentral_user_name ;
              } else {
                echo "&nbsp;" ;  
              }
          }
            ?>"><br />
			<div style="margin-top: 5px; width: 93%; border: 1px solid #004F6D; padding: 5px; background: #DAF0F8;">To prevent your number from being blocked, please use a Toll Free, SMS enabled phone number.  SMS charges may apply. [<a href="https://medium.com/ringcentral-developers/power-your-communications-with-toll-free-sms-cf8fdc77bc6e" target="_blank">Learn More</a>]</div>
		
		</td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "ringcentral_extension") echo "color:red"; ?>' >RingCentral Extension:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="ringcentral_extension" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['ringcentral_extension']);
          } else {             
              if ($result_rc->ringcentral_extension) { echo $result_rc->ringcentral_extension ; } 
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "ringcentral_password") echo "color:red"; ?>' >RingCentral Password:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="password" name="ringcentral_password" id="myRCPassword" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['ringcentral_password']);
          } else {        
              if ($result_rc->ringcentral_password) {
                echo ringcentral_decrypt($result_rc->ringcentral_password) ;
              } 
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "token_prefix") echo "color:red"; ?>' >Token Prefix:</p>
            <!--  <p style='color: red; display: inline'>*</p>   -->
             
            <?php echo ringcentral_build_help("token_prefix") ; ?>
                         
		</td>
		<td class="right_col"><input type="text" name="token_prefix" style="width: 25%;" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['token_prefix']);
          } else {             
              if ($result_rc->token_prefix) {
                  echo $result_rc->token_prefix ;
              } 
          }
            ?>"></td>
	</tr>	
    <?php /* =========== Team Messaging section ================= */ ?>
    <tr>
        <td colspan=2>
            <hr>
        </td>
    </tr>  
    
    <tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "enable_glip") echo "color:red"; ?>' >Activate Team Messaging?</p>
			
			<?php echo ringcentral_build_help("enable_glip") ; ?>
						
		</td>
		<td class="right_col"><input type="checkbox" name="enable_glip" <?php 
		if ($print_again) { 
		    if ($_POST['enable_glip'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($result_rc->enable_glip == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr>   
    
    <tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "embed_width") echo "color:red"; ?>' >Team Messaging Width:</p>
            <!--  <p style='color: red; display: inline'>*</p>   -->
             
            <?php echo ringcentral_build_help("embed_width") ; ?>
                         
		</td>
		<td class="right_col"><input type="text" name="embed_width" style="width: 25%;" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['embed_width']);
          } else {             
              if ($result_rc->embed_width) {
                  echo $result_rc->embed_width ;
              } 
          }
            ?>"> px</td>
	</tr>	
    <tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "embed_height") echo "color:red"; ?>' >Team Messaging Height:</p>
            <!--  <p style='color: red; display: inline'>*</p>   -->
             
            <?php echo ringcentral_build_help("embed_height") ; ?>
                         
		</td>
		<td class="right_col"><input type="text" name="embed_height" style="width: 25%;" value="<?php 
		  if ($print_again) {
		      echo sanitize_text_field($_POST['embed_height']);
          } else {             
              if ($result_rc->embed_height) {
                  echo $result_rc->embed_height ;
              } 
          }
            ?>"> px</td>
	</tr>	
	
	<?php /* ========= Google ReCaptcha Section =================== */ ?>
    <tr>
        <td colspan=2>
            <hr>
        </td>
    </tr>      
    
    <tr class="TableOverride">
        <td class="left_col">
            <p style='display: inline; <?php if ($label == "recaptcha_site") echo "color:red"; ?>' >Google ReCaptcha Site Key:</p>
            <p style='color: red; display: inline'>*</p>
        </td>
        <td class="right_col"><input type="password" name="recaptcha_site" id="myGRCSite" value="<?php 
          if ($print_again) {
              echo sanitize_text_field($_POST['recaptcha_site']);
          } else {             
              if ($result_rc->grc_site_key) {
                echo $result_rc->grc_site_key ;
              } 
          }
            ?>" > 
            </td>
    </tr>       
    <tr class="TableOverride">
        <td class="left_col">
            <p style='display: inline; <?php if ($label == "recaptcha_secret") echo "color:red"; ?>' >Google ReCaptcha Secret Key:</p>
            <p style='color: red; display: inline'>*</p>
        </td>
        <td class="right_col"><input type="password" name="recaptcha_secret" id="myGRCSecret" value="<?php 
          if ($print_again) {
              echo sanitize_text_field($_POST['recaptcha_secret']);
          } else {             
              if ($result_rc->grc_secret_key) {
                echo $result_rc->grc_secret_key ;
              } 
          }
            ?>" ><br />
            <div style="margin-top: 5px; width: 93%; border: 1px solid #004F6D; padding: 5px; background: #DAF0F8;">
            You need to register your site with Google ReCaptcha. Be sure to set up using the ReCaptcha Version 2 checkbox option. 
            To do that go here: [<a href="https://developers.google.com/recaptcha/" 
            target="_blank">Google ReCaptcha Version 2 Checkbox</a>]</div> 
            </td>
    </tr>     
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$btn_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","submit","",$btn_attributes); ?>
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
	
	$label = "" ;
	$message = "" ;
	
	if ($_POST['ringcentral_sandbox'] == "on") {
	    $sandbox = 1;
	} else {
	    $sandbox = 0;
	}    
	
	$rc_handshake = array(
	    "client_id"        => sanitize_text_field($_POST['client_id']),
	    "client_secret"    => sanitize_text_field($_POST['client_secret']),
	    "user_name"        => sanitize_text_field($_POST['ringcentral_user_name']) ,
	    "extension"        => sanitize_text_field($_POST['ringcentral_extension']) ,
	    "password"         => sanitize_text_field($_POST['ringcentral_password']) , 	    
	    "sandbox"          => $sandbox 	    
	);
	$GRCSite   = $_POST["recaptcha_site"] ;
	$GRCSecret = $_POST["recaptcha_secret"] ;
	
// 	/* data integrity checks */	
	if (ringcentral_validate_sdk($rc_handshake) == false) {
	    $print_again = true;
	    $label = "";
	    $message = "There was an error validating your Ring Central account credentials, please verify and try again";
	}
	if ($rc_handshake["client_id"] == "") {
	    $print_again = true;
	    $label = "client_id";
	    $message = "Client ID cannot be blank.";
	}	
	if ($rc_handshake["client_secret"] == "") {
	    $print_again = true;
	    $label = "client_secret";
	    $message = "Client Secret Key cannot be blank.";
	}
	if ($rc_handshake["user_name"] == "") {
	    $print_again = true;
	    $label = "ringcentral_user_name";
	    $message = "RingCentral User Name cannot be blank.";
	}
	if ($rc_handshake["extension"] == "") {
	    $print_again = true;
	    $label = "ringcentral_extension";
	    $message = "RingCentral extension cannot be blank.";
	}
	if ($rc_handshake["password"] == "") {
	    $print_again = true;
	    $label = "ringcentral_password";
	    $message = "RingCentral password cannot be blank.";
	}	
	if ($GRCSite == "") {
	    $print_again = true;
	    $label = "recaptcha_site";
	    $message = "Google ReCaptcha Site Key cannot be blank.";
	}	
	if ($GRCSecret == "") {
	    $print_again = true;
	    $label = "recaptcha_secret";
	    $message = "Google ReCaptcha Secret Key cannot be blank.";
	}
	/*
	if ($_POST['oauth_client'] == "") {
	    $print_again = true;
	    $label = "oauth_client";
	    $message = "OAuth Client Key cannot be blank.";
	}
	
	if ($_POST['oauth_secret'] == "") {
	    $print_again = true;
	    $label = "oauth_secret";
	    $message = "OAuth Secret Key cannot be blank.>";
	} */
	
	if ($_POST['embedded_phone'] == "on" && $_POST['enable_glip'] == "on" ) {
		$print_again = true;
		$label = "embedded_phone";
		$message = "Both embedded phone and team messaging cannot be activated at the same time.";
	}
	if ($_POST['embed_width'] <= 0 && $_POST['enable_glip'] == "on") {
		$print_again = true;
		$label = "embed_width";
		$message = "If you are activating embeded team messaging then the width setting cannot be blank and must be greater than 0";
	}
	if ($_POST['embed_height'] <= 0 && $_POST['enable_glip'] == "on") {
		$print_again = true;
		$label = "embed_height";
		$message = "If you are activating embeded team messaging then the height setting cannot be blank and must be greater than 0";
	}

	// end data integrity checking

	if ($print_again == true) {
		$color = "red" ;
	    show_form($message, $label, $color);
	} else {	    
	    /* convert and / or sanitize any needed form POST values */
	    if ($_POST['embedded_phone'] == "on") { 
	        $embedded_phone = 1;	        
        } else {
            $embedded_phone = 0;
        }
        if ($_POST['email_updates'] == "on") {
            $email_updates = 1;
        } else {
            $email_updates = 0;
        }        
        if ($_POST['mobile_updates'] == "on") {
            $mobile_updates = 1;
        } else {
            $mobile_updates = 0;
        } 
        if ($_POST['enable_glip'] == "on") {
        	$enable_glip = 1;
        } else {
        	$enable_glip = 0;
        }        
		
		$rc_handshake['password'] = ringcentral_encrypt($rc_handshake['password']);
        $token_prefix = sanitize_text_field($_POST['token_prefix']) ;
        $embed_width = sanitize_text_field($_POST['embed_width']) ;
        $embed_height = sanitize_text_field($_POST['embed_height']) ;
        
//         $oauth_client = $_POST['oauth_client'] ;
//         $oauth_secret = $_POST['oauth_secret'] ;

        $config_sql = $wpdb->prepare("UPDATE `ringcentral_control` SET
            `embedded_phone` = %d, `email_updates` = %d, `mobile_updates` = %d, `client_id` = %s, `client_secret` = %s,
            `ringcentral_user_name` = %s, `ringcentral_extension` = %d, `ringcentral_password` = %s, `ringcentral_sandbox` = %d,
        	`enable_glip` = %d, `embed_width` = %d,`embed_height` = %d,	
            `grc_site_key` = %s, `grc_secret_key` = %s, `token_prefix` = %s
            WHERE `ringcentral_control_id` = %d", $embedded_phone, $email_updates, $mobile_updates, $rc_handshake['client_id'], $rc_handshake['client_secret'], 
            $rc_handshake['user_name'], $rc_handshake['extension'], $rc_handshake['password'], $sandbox,
        	$enable_glip, $embed_width, $embed_height,	 
            $GRCSite, $GRCSecret, $token_prefix, 1) ;
                
        $wpdb->query( $config_sql ); 
        
	    $color = "#53DF00";
	    $message = "Configuration Changes have been saved";	   
	    show_form($message, $label, $color) ;	    
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