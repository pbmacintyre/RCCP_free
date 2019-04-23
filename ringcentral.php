<?php 
/*
Plugin Name: RCCP Free
Plugin URI:  https://ringcentral.com/
Description: RingCentral Communications Plugin - FREE
Author:      Peter MacIntyre
Version:     1.3.0
Author URI:  https://paladin-bs.com/peter-macintyre/
Details URI: https://paladin-bs.com
License:     GPL2
License URI: https://www.gnu.org/licenses/gpl-2.0.html

RCCP Free is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
any later version.
 
RCCP Free is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
 
See License URI for full details.
*/

/* ============================== */
/* Set RingCental Constant values */
/* ============================== */

if(!defined('RINGCENTRAL_PLUGINDIR')){
    define('RINGCENTRAL_PLUGINDIR', plugin_dir_path(__FILE__) ) ;
}
if(!defined('RINGCENTRAL_PLUGINURL')){
    define('RINGCENTRAL_PLUGINURL', plugin_dir_url(__FILE__) ) ;
    //  http path returned
}
if(!defined('RINGCENTRAL_PLUGIN_INCLUDES')){
    define('RINGCENTRAL_PLUGIN_INCLUDES', plugin_dir_path(__FILE__) . "includes/" ) ;
}
if(!defined('RINGCENTRAL_PLUGIN_FILENAME')){
    define ('RINGCENTRAL_PLUGIN_FILENAME', plugin_basename(dirname(__FILE__) . '/ringcentral.php') ) ;
}
if(!defined('RINGCENTRAL_PRO_URL')){
    define ('RINGCENTRAL_PRO_URL', 'https://paladin-bs.com/product/rccp-pro/') ;
}
if(!defined('RINGCENTRAL_LOGO')){
    define ('RINGCENTRAL_LOGO', RINGCENTRAL_PLUGINURL . 'images/ringcentral-logo.png' ) ;
}

/* ====================================== */
/* bring in generic ringcentral functions */
/* ====================================== */
require_once("includes/ringcentral-functions.inc");

/* ================================= */
/* set ring central supporting cast  */
/* ================================= */
function ringcentral_js_add_script() {
    $js_path = RINGCENTRAL_PLUGINURL . 'js/ringcentral-scripts.js' ;
    wp_enqueue_script('ringcentral-js', $js_path) ;    
}
add_action('init', 'ringcentral_js_add_script');

function ringcentral_load_custom_admin_css() {
    wp_register_style( 'ringcentral_custom_admin_css', 
        RINGCENTRAL_PLUGINURL . 'css/ringcentral-custom.css', 
        false, '1.0.0' );
    wp_enqueue_style( 'ringcentral_custom_admin_css' );
}

add_action( 'admin_print_styles', 'ringcentral_load_custom_admin_css' );

/* ========================================= */
/* Make top level menu                       */
/* ========================================= */
function ringcentral_menu(){
    add_menu_page(
        'RCCP Free: RingCentral Configurations',    // Page & tab title
        'RCCP Free',                                // Menu title
        'manage_options',                           // Capability option
        'ringcentral_Admin',                        // Menu slug
        'ringcentral_config_page',                  // menu destination function call
        RINGCENTRAL_PLUGINURL . 'images/ringcentral-icon.png', // menu icon path
//         'dashicons-phone', // menu icon path from dashicons library
        25 );                                       // menu position level         
     
    add_submenu_page(
        'ringcentral_Admin',                   // parent slug
        'RCCP Free: RingCentral Configurations', // page title
        'Settings',                            // menu title - can be different than parent
        'manage_options',                      // options
        'ringcentral_Admin' );                 // menu slug to match top level (go to the same link)
    
    add_submenu_page(
        'ringcentral_Admin',                // parent menu slug
        'RCCP Free: RingCentral Add a New Subscriber', // page title
        'Add Subscribers',                  // menu title
        'manage_options',                   // capability
        'ringcentral_add_subs',             // menu slug
        'ringcentral_add_subscribers'       // callable function
        );    
    add_submenu_page(
        'ringcentral_Admin',                   // parent menu slug
        'RCCP Free: RingCentral Manage Subscribers', // page title
        'List Subscribers',                    // menu title
        'manage_options',                      // capability
        'ringcentral_list_subs',               // menu slug
        'ringCentral_list_subscribers'         // callable function
        );    
    add_submenu_page(
        'ringcentral_Admin',                // parent menu slug
        'RCCP Free: RingCentral CallMe Requests', // page title
        'Call Me Requests',                 // menu title
        'manage_options',                   // capability
        'ringcentral_list_callme',          // menu slug
        'ringCentral_list_callme_requests'  // callable function
        );    

}  

/* ========================================= */
/* page / menu calling functions             */
/* ========================================= */

// call add action func on menu building function above.
add_action('admin_menu', 'ringcentral_menu');

// function for default Admin page
function ringcentral_config_page() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
?>    
    <div class="wrap">
        <img id='page_title_img' title="RingCentral Plugin" src="<?= RINGCENTRAL_LOGO ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
        <?php require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-config-page.inc"); ?>
        
    </div>
    <?php
}

// function for adding new subscribers page
function ringcentral_add_subscribers() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    ?>
    <div class="wrap">
        <img id='page_title_img' title="RingCentral Plugin" src="<?= RINGCENTRAL_LOGO ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
       <?php require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-add-subscribers.inc"); ?>
       
    </div>
    <?php
}

// function for editing existing subscribers page
function ringCentral_list_subscribers() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    ?>
        
    <div class="wrap">
        <img id='page_title_img' title="RingCentral Plugin" src="<?= RINGCENTRAL_LOGO ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
       <?php require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-list-subscribers.inc"); ?>
       
    </div>
    <?php
}
// function for editing existing subscribers page
function ringCentral_list_callme_requests() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    ?>
        
    <div class="wrap">
        <img id='page_title_img' title="RingCentral Plugin" src="<?= RINGCENTRAL_LOGO ;?>">
        <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
        
       <?php require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-list-callme.inc"); ?>
       
    </div>
    <?php
}

/* ========================================================== */ 
/* Add action for the ringcentral Embedded Phone app toggle   */
/* ========================================================== */
add_action('admin_footer', 'ringcentral_embed_phone');	

/* =============================================== */
/* Add custom footer action                        */
/* This toggles the ringcentral Embedded Phone app */
/* =============================================== */
function ringcentral_embed_phone() {
    global $wpdb;    
    $result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `embedded_phone` 
        FROM `ringcentral_control`
        WHERE `ringcentral_control_id` = %d", 1)
    );    
    if ($result_rc->embedded_phone == 1) { ?>
    	<script src="https://ringcentral.github.io/ringcentral-embeddable-voice/adapter.js"></script>
    <?php } 
}
/* ================================== */
/* Add action for the contacts widget */
/* ================================== */
add_action('widgets_init', 'ringcentral_register_contacts_widget');

/* ============================================== */
/* Add contacts widget function                   */
/* This registers the ringcentral_contacts_widget */
/* ============================================== */
function ringcentral_register_contacts_widget() {
  register_widget('ringcentral_contacts_widget') ;   
}

require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-contacts-widget.inc"); 

/* ================================= */
/* Add action for the Call Me widget */
/* ================================= */
add_action('widgets_init', 'ringcentral_register_callme_widget');

/* ============================================ */
/* Add Call Me widget function                  */
/* This registers the ringcentral_callme_widget */
/* ============================================ */
function ringcentral_register_callme_widget() {
     register_widget('ringcentral_callme_widget') ;
}

require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-callme-widget.inc"); 

/* ============================================== */
/* Add action hook for correspondence on new post */
/* ============================================== */
add_action( 'pending_to_publish', 'ringcentral_new_post_set_queue');
add_action( 'draft_to_publish', 'ringcentral_new_post_set_queue');

function ringcentral_new_post_set_queue( $post) {
	global $wpdb ;
	
	if (wp_is_post_revision( $post->ID ) || get_post_type($post->ID) !== 'post') { return; }
	
	$post_url = get_permalink( $post->ID );
	$title = $post->post_title;
	
	$wpdb->query($wpdb->prepare("INSERT INTO `ringcentral_queue` 
        (`ringcentral_post_id`, `ringcentral_post_title`, `ringcentral_post_url`) 
        VALUES (%d, %s, %s)", $post->ID, $title, $post_url));
}

/* ============================================== */
/* Setup CRON to do SMS messages and emails .     */
/* ============================================== */
function ringcentral_cron_schedules($schedules){
    if(!isset($schedules["5min"])){
        $schedules["5min"] = array(
            'interval' => 5*60,
            'display' => __('Once every 5 minutes'));
    }
    if(!isset($schedules["30min"])){
        $schedules["30min"] = array(
            'interval' => 30*60,
            'display' => __('Once every 30 minutes'));
    }
    return $schedules;
}
add_filter('cron_schedules','ringcentral_cron_schedules');

if ( ! wp_next_scheduled( 'ringcentral_send_notifications' ) ) {
  wp_schedule_event( time(), '5min', 'ringcentral_send_notifications' );
}

add_action( 'ringcentral_send_notifications', 'ringcentral_check_queue' );

function ringcentral_check_queue() {
	global $wpdb;
	
	$result_queue = $wpdb->get_row( $wpdb->prepare("SELECT `ringcentral_queue_id` AS `id`, 
        `ringcentral_post_title` AS `title`, `ringcentral_post_url` AS `url`
        FROM `ringcentral_queue`
        WHERE `ringcentral_queue_complete` = %d LIMIT 1", 0)
    );
	
	if($result_queue) {
		$siteName = get_bloginfo('name');
		$queueId = $result_queue->id;
		$postTitle = $result_queue->title;
		$postUrl = $result_queue->url;
		
		$wpdb->query($wpdb->prepare("UPDATE `ringcentral_queue` 
            SET `ringcentral_queue_complete` = 1 WHERE `ringcentral_queue_id` = %d", $queueId));
		
		$result_rc = $wpdb->get_row( $wpdb->prepare("SELECT `email_updates`, `mobile_updates`
			FROM `ringcentral_control`
			WHERE `ringcentral_control_id` = %d", 1)
		);
		
		if ($result_rc->email_updates) { 
			require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-send-mass-email.inc"); 
		}
		
        if ($result_rc->mobile_updates) {
			require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-send-mass-mobile.inc"); 
		}
	}
}


/* ============================================== */
/* Add filter hook for subscriptions */
/* ============================================== */
function ringcentral_vars($vars) {
	$vars[] = 'rcsubscribe';
	$vars[] = 'rcunsubscribe';
	$vars[] = 'rcformat';
	$vars[] = 'rcwebhook';
	return $vars;
}

add_filter('query_vars', 'ringcentral_vars');


function ringcentral_handle_vars() {	
	global $wpdb;
	$subscribe = get_query_var('rcsubscribe');
	$unsubscribe = get_query_var('rcunsubscribe');
	$method = get_query_var('rcformat');
	
	if (!empty($subscribe)) {
		$token_id = $subscribe;
		require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-confirm-optin.inc");
	} elseif (!empty($unsubscribe)) {
		$token_id = $unsubscribe;
		require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-unsubscribe.inc");
	} elseif (!empty(get_query_var('rcwebhook'))) {
		// Check for opt out keywords
		require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-webhook.inc");
	}
}

add_action('parse_query', 'ringcentral_handle_vars');


/* ============================================= */
/* Add registration hook for plugin installation */
/* ============================================= */
function ringcentral_install() {
    require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-install.inc");
}
/* ========================================= */
/* Create default pages on plugin activation */
/* ========================================= */
function ringcentral_install_default_pages(){
    require_once(RINGCENTRAL_PLUGINDIR . "includes/ringcentral-activation.inc");
}

register_activation_hook(__FILE__, 'ringcentral_install');
register_activation_hook(__FILE__, 'ringcentral_install_default_pages');



/* ===================================== */
/* Check if the pro version is available */
/* ===================================== */
if (ringcentral_CheckPro()) { 
    /* ====================================================== */
    /* add link on plugin details line for buying Pro Version */
    /* ====================================================== */
    add_filter('plugin_row_meta', 'rc_get_pro', 10, 2);
    
    //Add a link on the plugin control line after 'visit plugin site'
    function rc_get_pro($links, $file) {
        if ( $file == RINGCENTRAL_PLUGIN_FILENAME ) {
            $link_string = RINGCENTRAL_PRO_URL ;
            $links[] = "<a href='$link_string' style='color: red' target='_blank'>" . esc_html__('Get Pro Version', 'RCCP_free') . '</a>';
        }
        return $links;
    }
}
?>