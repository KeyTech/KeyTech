/* 
 * File:   errorHandling.cpp
 * Author: torisuta
 *
 * Created on May 10, 2012, 10:40 AM
 */

#include "errorHandling.h"

// SocketException Code
ErrorHandling::ErrorHandling(const string &message, bool inclSysMsg) throw() 
: userMessage(message) {
  if (inclSysMsg) {
  } 
}

ErrorHandling::~ErrorHandling() throw() {
    
}

const char *ErrorHandling::what() const throw() {
    
  return userMessage.c_str();
}


