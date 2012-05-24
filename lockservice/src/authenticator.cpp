/* 
 * File:   authenticator.cpp
 * Author: tristan
 * 
 * Created on May 20, 2012, 10:45 PM
 */

#include "authenticator.h"

Authenticator::Authenticator() {
}

Authenticator::~Authenticator() {
}

ResponseAnswer Authenticator::authenticate(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode){
    
   DataBaseConnector DBconnector;
   
   if(DBconnector.mysql_get_query(KeyIdentifier, UserIdentifier, Pincode)){
      return PERMISSION_GRANTED;
   } else {
      return NO_ACCESS; 
   }
     
}

