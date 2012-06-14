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
#include "Logger.h"

using namespace std;

class DataBaseConnector {
public:
  
  DataBaseConnector(); 
    
  ~DataBaseConnector();
  
  MYSQL* mysql_connection_setup(const char *server, const char *user, const char *password, const char *database);
  
  MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query);
  
  void mysql_set_query_user_permission();
  
  void mysql_set_query_access_rights();
  
  ResponseAnswer mysql_get_permission();
  
  bool mysql_get_access_type();
  
  void mysql_set_query_information(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode);
  
  void userLogging(ResponseAnswer theResult);
  
  string responseAnswerConverter(ResponseAnswer theResult);
  
  void countLogTries(uint32_t UserIdentifier);
  
  void updateUserStatus();
   
private:  
  stringstream ss; 
  
  struct qrStruct {       
        uint16_t KeyIdentifier;
        uint32_t UserIdentifier;
        uint16_t PinCode;       
  } queryStruct;
  
  
protected:

  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_RES *logres;
  MYSQL_ROW row;
};

#endif	/* DBCONNECTOR_H */

