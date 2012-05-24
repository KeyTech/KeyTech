/* 
 * File:   dbconnector.cpp
 * Author: torisuta
 * 
 * Created on May 9, 2012, 9:53 AM
 */

#include "DataBaseConnector.h"

DataBaseConnector::DataBaseConnector() {
  
  const char *server = "localhost"; 
  const char *user = "keytech";
  const char *password = "appelmoes";
  const char *database = "lockservice";
      
  conn = mysql_init(NULL);
 
  // connect to the database with the details attached.
  mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
}

DataBaseConnector::~DataBaseConnector() {
    
  mysql_close(conn);
}

bool DataBaseConnector::mysql_get_query(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode) {
    
            
   MYSQL_RES *result;
   int num_result;
   string s;
   stringstream out;

    out << "SELECT R.lockIdentifier, U.userIdentifier, U.pincode "
           "FROM reservation R "
           "JOIN userAccessGroup G ON R.groupName = G.groupName "
           "JOIN user U ON G.userIdentifier = U.userIdentifier "
           "JOIN reservationTime T ON R.reservationTimeName = T.name "
           "WHERE R.lockIdentifier = " << KeyIdentifier <<
           " AND U.userIdentifier = " << UserIdentifier <<
           " AND U.pincode = " << Pincode <<
           " AND T.startTime <= CURRENT_TIME() AND T.endTime >= CURRENT_TIME()"
           " AND R.startDate <= CURRENT_DATE() AND (R.endDate >= CURRENT_DATE()"
           " OR R.endDate IS NULL)" 
           " AND ("
           " R.repeatInterval = 'DAY' OR"
           " (R.repeatInterval = 'WEEK' AND DAYOFWEEK(CURRENT_DATE()) = DAYOFWEEK(R.startDate)))" 
           " OR"
           " (R.repeatInterval = 'MONTH' AND DAYOFMONTH(CURRENT_DATE()) = DAYOFMONTH(R.startDate))";
     
    s = out.str();

    char * cstr;
    cstr = new char[s.size()+1];
    strcpy(cstr, s.c_str());
  
  if(mysql_query(conn, cstr) == 1){
      return false;
      
  } else {
     
    result = mysql_store_result(conn); 
    num_result = mysql_num_rows(result);  
    mysql_free_result(result);
    
    out.str("");
    delete[] cstr;
     
    if(num_result > 0){
       printf("User found ! \n");
       return true;
    } else {
       printf("User not found ! \n");
       return false;
    }
  } 
}
