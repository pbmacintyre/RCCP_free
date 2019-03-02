<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions
 *
 */

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "#008EC2") {	
	global $print_again, $wpdb;    ?>    
    
    <form action="<?php echo RINGCENTRAL_PRO_URL ?>" target="_blank" style="padding-left: 15%;">
        <?php 
        $btn_attributes = array( "style" => "background: red; border-color: #006799; color: #fff;" ); 
        submit_button("Get Pro Version","","submit","",$btn_attributes);
        ?>        
    </form>
    	
	<form action="" method="post" >
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
	if ($print_again == true) {
		echo "<font color='$color'><strong>" . $message . "</strong></font>";
	} else {
	    echo "<font color='$color'><strong>" . $message . "</strong></font>";
	}
	
	$result_rc = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `ringcentral_control` WHERE `ringcentral_control_id` = %d", 1) );
	
	?></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "embedded_phone") echo "color:red"; ?>' >Use Embedded Phone?</p>			
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
            
            <?php echo build_help("ringcentral_sandbox") ; ?>
                      
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
			<p style='display: inline; <?php if ($label == "client_id") echo "color:red"; ?>' >Client ID:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="client_id" value="<?php 
		  if ($print_again) {
		      echo $_POST['client_id'];
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
		<td class="right_col"><input type="password" name="client_secret" value="<?php 
		  if ($print_again) {
		      echo $_POST['client_secret'];
          } else {             
              if ($result_rc->client_secret) {
                echo $result_rc->client_secret ;
              } 
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
		<p style='display: inline; <?php if ($label == "ringcentral_user_name") echo "color:red"; ?>' >Username:</p>
		<p style='color: red; display: inline'>*</p>
        
        <?php echo build_help("username") ; ?>
              
		</td>
		<td class="right_col"><input type="text" name="ringcentral_user_name" value="<?php 
		  if ($print_again) {
		      echo $_POST['ringcentral_user_name'];
          } else {             
              if ($result_rc->ringcentral_user_name) {
                echo $result_rc->ringcentral_user_name ;
              } else {
                echo "&nbsp;" ;  
              }
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "ringcentral_extension") echo "color:red"; ?>' >RingCentral Extension:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col"><input type="text" name="ringcentral_extension" value="<?php 
		  if ($print_again) {
		      echo $_POST['ringcentral_extension'];
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
		<td class="right_col"><input type="password" name="ringcentral_password" value="<?php 
		  if ($print_again) {
		      echo $_POST['ringcentral_password'];
          } else {             
              if ($result_rc->ringcentral_password) {
                echo $result_rc->ringcentral_password ;
              } 
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "token_prefix") echo "color:red"; ?>' >Token Prefix:</p>
            <!--  <p style='color: red; display: inline'>*</p>   -->
             
            <?php echo build_help("token_prefix") ; ?>
                         
		</td>
		<td class="right_col"><input type="text" name="token_prefix" style="width: 25%;" value="<?php 
		  if ($print_again) {
		      echo $_POST['token_prefix'];
          } else {             
              if ($result_rc->token_prefix) {
                  echo $result_rc->token_prefix ;
              } 
          }
            ?>"></td>
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
	    "client_id"        => $_POST['client_id'],
	    "client_secret"    => $_POST['client_secret'],
	    "user_name"        => $_POST['ringcentral_user_name'] ,
	    "extension"        => $_POST['ringcentral_extension'] ,
	    "password"         => $_POST['ringcentral_password'] , 	    
	    "sandbox"          => $sandbox 	    
	);
	
// 	/* data integrity checks */	
	if (ringcentral_validate_sdk($rc_handshake) == false) {
	    $print_again = true;
	    $label = "";
	    $message = "There was an error validating your Ring Central account credentials, please verify and try again";
	}
	if ($rc_handshake["client_id"] == "") {
	    $print_again = true;
	    $label = "client_id";
	    $message = "<b>Client ID cannot be blank.</b>";
	}	
	if ($rc_handshake["client_secret"] == "") {
	    $print_again = true;
	    $label = "client_secret";
	    $message = "<b>Client Secret Key cannot be blank.</b>";
	}
	if ($rc_handshake["user_name"] == "") {
	    $print_again = true;
	    $label = "ringcentral_user_name";
	    $message = "<b>RingCentral User Name cannot be blank.</b>";
	}
	if ($rc_handshake["extension"] == "") {
	    $print_again = true;
	    $label = "ringcentral_extension";
	    $message = "<b>RingCentral extension cannot be blank.</b>";
	}
	if ($rc_handshake["password"] == "") {
	    $print_again = true;
	    $label = "ringcentral_password";
	    $message = "<b>RingCentral password cannot be blank.</b>";
	}	
	/*
	if ($_POST['oauth_client'] == "") {
	    $print_again = true;
	    $label = "oauth_client";
	    $message = "<b>OAuth Client Key cannot be blank.</b>";
	}
	
	if ($_POST['oauth_secret'] == "") {
	    $print_again = true;
	    $label = "oauth_secret";
	    $message = "<b>OAuth Secret Key cannot be blank.</b>";
	} */

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
        
        $token_prefix          = $_POST['token_prefix'] ;
        
//         $oauth_client = $_POST['oauth_client'] ;
//         $oauth_secret = $_POST['oauth_secret'] ;

        $config_sql = $wpdb->prepare("UPDATE `ringcentral_control` SET
            `embedded_phone` = %d, `email_updates` = %d, `mobile_updates` = %d, `client_id` = %s, `client_secret` = %s,
            `ringcentral_user_name` = %s, `ringcentral_extension` = %d, `ringcentral_password` = %s, `ringcentral_sandbox` = %d, `token_prefix` = %s
            WHERE `ringcentral_control_id` = %d", $embedded_phone, $email_updates, $mobile_updates, $rc_handshake['client_id'], $rc_handshake['client_secret'], 
            $rc_handshake['user_name'], $rc_handshake['extension'], $rc_handshake['password'], $sandbox, $token_prefix, 1) ;
                
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