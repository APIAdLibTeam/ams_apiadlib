<?php

/**
  * @file
  * AMS APIAdLib functions include file  
  */
  
/**
 * Function loads library apiadlib
 */ 
function ams_apiadlib_load_library() {

  //DONE: check how works autoloads
  //DONE: sign that library already loaded and checkin it
  
  $libloaded = &drupal_static(__FUNCTION__);
  
  if(!isset($libloaded)||!$libloaded) {
    try {
      
      $libloaded = module_load_include('php', 'ams_apiadlib', 'apiadlib/apiadlib.autoload');
      
      } catch (Exception $e) {
      
      watchdog_exception('ams_apiadlib', $e, NULL, WATCHDOG_ERROR);
      
      }
    }
    
  return $libloaded;
}
  
/**
 * Create AMS user with given auth and connection settings
 */
function ams_apiadlib_create_user($ams_auth) {

  $ams_user = FALSE;
  
  if(is_object($ams_auth)) {
    try {
      if($ams_auth->type == 'ydirect') {
        $ams_user = new YDirectUserExt($ams_auth->auth, $ams_auth->settings);
        } elseif($ams_auth->type == 'adwords') {
        $ams_user = new AdWordsUserExt($ams_auth->auth, $ams_auth->settings);
        }
      } catch (Exception $e) {
      watchdog_exception('ams_apiadlib', $e, NULL, WATCHDOG_ERROR);
      $ams_user = FALSE;
      }
    }
     
   return $ams_user;   
} 

/**
 * Function create new SOAP client
 */ 
function ams_apiadlib_create_soap_client($ams_auth, $ams_user, $wsdl = NULL, $soap_options = array()) {

  $ams_client = FALSE;
  if(is_object($ams_auth)) {
    try {
    
      if($ams_auth->type == 'ydirect') {
      
        //DEBUG:
        $soap_options['trace'] = 1;
        
        $ams_client = new YDirectSoapClient($wsdl, $soap_options, $ams_user,  
          $ams_auth->service_name, $ams_auth->service_namespace);
        
        } elseif($ams_auth->type == 'adwords') {
        
        $ams_client = new AdWordsSoapClient($wsdl, $soap_options, $ams_user, 
          $ams_auth->serviceName, $ams_auth->serviceNamespace);
        
        }
      } catch (Exception $e) {
      $ams_client = FALSE;
      watchdog_exception('ams_apiadlib', $e, NULL, WATCHDOG_ERROR);
      }
    }
      
  return $ams_client;
}

/**
 * Function for checking connections to ads systems
 */
function ams_apiadlib_test_auth_html($soap_client) {
  $html = '';
  
  if(!is_object($soap_client)) {
    return 'ERROR: SOAP Client object required';
    }
  
  //DEBUG:
  //dvr($soap_client);
  
  if($soap_client->ams_auth->type == 'ydirect') {
    $responce = $soap_client->PingAPI();
    $html .= '<p>';
    $html .= 'Ping API - ';
    $html .= ($responce == '1' ? '<font color=green>Ok</font>.' : '<font color=red>Failed</font>.');
    $html .= '</p>';
    

    $responce = $soap_client->GetVersion();
    $html .= '<p>';
    $html .= 'Current version - ';
    $html .= '<font color=green>'.$responce.'</font>';
    $html .= '</p>';
    
    } elseif($soap_client->ams_auth->type == 'adwords') {
    $html .= 'Google AdWords temporarily not supported';
    }
  
  return $html;
} 
  
