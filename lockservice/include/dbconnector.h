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
#include <mysql.h>
#include <string>

using namespace std;

class dbconnector {
public:
  
  dbconnector(); 
    
  ~dbconnector();
  
  MYSQL * mysql_connection_setup(const char *server, const char *user, const char *password, const char *database);
  
  MYSQL_RES * mysql_perform_query(MYSQL *connection, char *sql_query);
  
  //char * stringToChar(string stringName);
  
  void mysql_get_query();
  
private:
    
protected:

  MYSQL *conn;
    
};

#endif	/* DBCONNECTOR_H */

