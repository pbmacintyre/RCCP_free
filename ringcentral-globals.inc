<?php 
/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */

/* ============================== */
/* Set RingCental Constant values */
/* ============================== */

if(!defined('RINGCENTRAL_PLUGINDIR')){
    define('RINGCENTRAL_PLUGINDIR', plugin_dir_url(__FILE__) ) ;
}
if(!defined('RINGCENTRAL_PLUGIN_INCLUDES')){
    define('RINGCENTRAL_PLUGIN_INCLUDES', plugin_dir_url(__FILE__) . "includes/" ) ;
}
if(!defined('RINGCENTRAL_PLUGIN_FILENAME')){
    define ('RINGCENTRAL_PLUGIN_FILENAME', plugin_basename(dirname(__FILE__) . '/ringcentral.php') ) ;    
}
if(!defined('RINGCENTRAL_PRO_URL')){
    define ('RINGCENTRAL_PRO_URL', 'https://paladin-bs.com/product/rccp-pro/') ;
}
if(!defined('RINGCENTRAL_LOGO')){
    define ('RINGCENTRAL_LOGO', RINGCENTRAL_PLUGINDIR . 'images/ringcentral-logo.png' ) ;
}
/* ============================================ */
if(!defined('RINGCENTRAL_SPACER')){
    $spacer = "<br/>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; " ;
    define ('RINGCENTRAL_SPACER', $spacer) ;
}
?>