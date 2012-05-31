/* 
 * File:   authenticator.cpp
 * Author: tristan
 * 
 * Created on May 20, 2012, 10:45 PM
 */

#include "authenticator.h"

Authenticator::Authenticator() {
    dbconnector = new DataBaseConnector();
}

Authenticator::~Authenticator() {
}

ResponseAnswer Authenticator::authenticate(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode){
    
  dbconnector->mysql_set_query_information(KeyIdentifier, UserIdentifier, Pincode);
     
  if(dbconnector->mysql_get_access_type()){
       
    return PERMISSION_GRANTED;  
      
  } else {
          
    return dbconnector->mysql_get_permission();     
  }    
}

