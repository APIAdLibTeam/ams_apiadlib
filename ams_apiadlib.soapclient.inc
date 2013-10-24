<?php

/**
  * @file
  * AMS APIAdLib SOAP Client class  
  */
  
class AMSAPIAdlibSOAPClient {

  public $user;
  public $soap_client;
  public $ams_auth;
  public $wsdl;
  public $soap_options;
  
  public function __construct($ams_auth, $wsdl = NULL, $soap_options = array()) {
  
    module_load_include('inc', 'ams_apiadlib', 'ams_apiadlib.functions');
  
    $this->ams_auth = $ams_auth;
    $this->wsdl = $wsdl;
    $this->soap_options = $soap_options;
    
    $this->createObjects();
    }

  protected function createObjects() {
    //DEBUG:
    //ddebug_backtrace();
    
    ams_apiadlib_load_library();
    $this->user = ams_apiadlib_create_user($this->ams_auth);
    //DEBUG:
    //$resp = $this->user->GetClientsList();
    //kpr($resp);
    
    if($this->user) {
      $this->soap_client = ams_apiadlib_create_soap_client($this->ams_auth, 
        $this->user, $this->wsdl, $this->soap_options);
      //DEBUG:
      //$resp = $this->soap_client->GetClientsList();
      //kpr($resp);
      }
    }
    
  public function __call($name, $arguments) {
    if(isset($this->soap_client)&&$this->soap_client) {
      //DEBUG:
      //dargs();
      
      if(count($arguments) > 0) {
        $resp = $this->soap_client->$name($arguments);
        } else {
        $resp = $this->soap_client->$name();
        }
      //DEBUG:
      //kpr($resp);
      return $resp;
      } else {
      throw new Exception(t('No SOAP Client object'), 0);
      }
    }
    
  public function getLogin() {
    if($this->user) {
      return $this->user->GetLogin();
      }
    return NULL;
    }
    
  }  
