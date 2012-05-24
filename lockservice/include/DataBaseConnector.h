/* 
 * File:   dbconnector.h
 * Author: torisuta
 *
 * Created on May 9, 2012, 9:53 AM
 */

#ifndef DBCONNECTOR_H
#define	DBCONNECTOR_H

#include "errorHandling.h"
#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Defines.h"

using namespace std;

class DataBaseConnector {
public:
  
  DataBaseConnector(); 
    
  ~DataBaseConnector();
  
  bool mysql_get_query(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode);
    
protected:

  MYSQL *conn;
    
};

#endif	/* DBCONNECTOR_H */

