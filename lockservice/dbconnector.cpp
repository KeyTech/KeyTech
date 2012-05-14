/* 
 * File:   dbconnector.cpp
 * Author: torisuta
 * 
 * Created on May 9, 2012, 9:53 AM
 */

#include "dbconnector.h"

dbconnector::dbconnector() {
  
  const char *server = "localhost"; 
  const char *user = "root";
  const char *password = "test";
  const char *database = "mysql";
      
  conn = mysql_connection_setup(server, user, password, database);
}

dbconnector::~dbconnector() {
    
  mysql_close(conn);
}

//char * dbconnector::stringToChar(string stringName) {
  
 //char *buf = new char[stringName.size()];
	    
// return strcpy(buf, stringName.c_str()); 
//}

MYSQL * dbconnector::mysql_connection_setup(const char *server, const char *user, const char *password, const char *database){
    
  // first of all create a mysql instance and initialize the variables within
  MYSQL *connection = mysql_init(NULL);
 
  // connect to the database with the details attached.
  mysql_real_connect(connection, server, user, password, database, 0, NULL, 0);
    
  return connection;
}

void dbconnector::mysql_get_query() {
    
  MYSQL_RES *res;
  MYSQL_ROW row;
    
  res = mysql_perform_query(conn, (char *) "show tables");
    
  while ((row = mysql_fetch_row(res)) !=NULL)
  printf("\t-&gt; %s -&gt; %s \n", row[0],row[1]);
    
  mysql_free_result(res);
}

MYSQL_RES * dbconnector::mysql_perform_query(MYSQL *connection, char *sql_query) {
    
  // send the query to the database
  mysql_query(connection, sql_query);
 
  return mysql_use_result(connection);
}

