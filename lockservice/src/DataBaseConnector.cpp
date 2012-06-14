/* 
 * File:   dbconnector.cpp
 * Author: torisuta
 * 
 * Created on May 9, 2012, 9:53 AM
 */

#include "DataBaseConnector.h"


DataBaseConnector::DataBaseConnector() {
    
  const char *server = "localhost"; 
  const char *user = "root";
  const char *password = "test";
  const char *database = "slotservice";
  
  conn = mysql_connection_setup(server, user, password, database);  
}

DataBaseConnector::~DataBaseConnector() {
    
  mysql_close(conn);
}

void DataBaseConnector::mysql_set_query_information(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode){
  queryStruct.KeyIdentifier = KeyIdentifier;
  queryStruct.UserIdentifier = UserIdentifier;
  queryStruct.PinCode = Pincode;
}

MYSQL* DataBaseConnector::mysql_connection_setup(const char *server, const char *user, const char *password, const char *database)
{
     // first of all create a mysql instance and initialize the variables within
    MYSQL *connection = mysql_init(NULL);
 
    // connect to the database with the details attached.
    if (!mysql_real_connect(connection, server, user, password, database, 0, NULL, 0)) {
      printf("Conection error : %s\n", mysql_error(connection));
      exit(1);
    }
    return connection;
}

MYSQL_RES* DataBaseConnector::mysql_perform_query(MYSQL *connection, char *sql_query)
{
  // send the query to the database
  if (mysql_query(connection, sql_query))
  {
    printf("MySQL query error : %s\n", mysql_error(connection));
    exit(1);
  }
 
  return mysql_store_result(connection);
}

void DataBaseConnector::mysql_set_query_access_rights(){
  string s;
  stringstream out;
 
  out << "SELECT U.pincode, U.userIdentifier, RU.lockIdentifier "
         "FROM user U "
         "JOIN userAccessGroup G ON U.userIdentifier = G.userIdentifier "
         "JOIN accessGroupUnlimitedAccess A ON G.groupName = A.groupName "
         "JOIN roomUnlimitedAccess RU ON A.unlimitedAccessName = RU.unlimitedAccessName "
         "JOIN reservation R ON G.groupName = R.groupName "
         "WHERE RU.lockIdentifier = " << queryStruct.KeyIdentifier <<
         " AND U.userIdentifier = " << queryStruct.UserIdentifier;
     
  s = out.str();

  char * cstr;
  cstr = new char[s.size()+1];
  strcpy(cstr, s.c_str());
    
  res = mysql_perform_query(conn, cstr);
      
  out.str("");
  delete[] cstr;
}

void DataBaseConnector::mysql_set_query_user_permission() {           
  string s;
  stringstream out;

  out << "SELECT R.lockIdentifier, U.userIdentifier, U.pincode, U.blocked "
         "FROM reservation R "
         "JOIN userAccessGroup G ON R.groupName = G.groupName "
         "JOIN user U ON G.userIdentifier = U.userIdentifier "
         "JOIN reservationTime T ON R.reservationTimeName = T.name "           
         "WHERE R.lockIdentifier = " << queryStruct.KeyIdentifier <<
         " AND U.userIdentifier = " << queryStruct.UserIdentifier <<
         " AND (T.startTime <= CURRENT_TIME() AND T.endTime >= CURRENT_TIME()"
         " AND R.startDate <= CURRENT_DATE() AND (R.endDate >= CURRENT_DATE()"
         " OR R.endDate IS NULL)" 
         " AND ("
         " R.repeatInterval = 'DAY' OR"
         " (R.repeatInterval = 'WEEK' AND DAYOFWEEK(CURRENT_DATE()) = DAYOFWEEK(R.startDate)))" 
         " OR"
         " (R.repeatInterval = 'MONTH' AND DAYOFMONTH(CURRENT_DATE()) = DAYOFMONTH(R.startDate)))";
     
  s = out.str();

  char * cstr;
  cstr = new char[s.size()+1];
  strcpy(cstr, s.c_str());
    
  res = mysql_perform_query(conn, cstr);
      
  out.str("");
  delete[] cstr;
}  

/**
 *  Look what kind of persmission the user has
 */
ResponseAnswer DataBaseConnector::mysql_get_permission(){
  int num_result = 0;
  string strResult;
  ostringstream convert;  
  char *cstr;
  
  // Make the query
  mysql_set_query_user_permission();
  num_result = mysql_num_rows(res);
  row = mysql_fetch_row(res);
  mysql_free_result(res);
  
  // Int to char*
  convert << queryStruct.PinCode;
  strResult = convert.str();
  cstr = new char[strResult.size()];
  strcpy(cstr, strResult.c_str());
  
  if(num_result > 0){      
    if((strcmp(row[3], "0") == 0) && (strcmp(row[2], cstr) == 0)){
     
      ss << "User[" << queryStruct.UserIdentifier << "] has Permission for key[" << queryStruct.KeyIdentifier << "].";
      Logger::debug(ss.str());   
      
      userLogging(PERMISSION_GRANTED);
      return PERMISSION_GRANTED;
    } else if((strcmp(row[3], "1") == 0) && ((strcmp(row[2], cstr) == 0) || (strcmp(row[2], cstr) != 0))) {
      
      ss << "User[" << queryStruct.UserIdentifier << "] is blocked.";
      Logger::debug(ss.str()); 
      
      userLogging(USER_BLOCKED);
      return USER_BLOCKED;
    } else if((strcmp(row[3], "0") == 0) && (strcmp(row[2], cstr) != 0))  {
      
      countLogTries(queryStruct.UserIdentifier);
      row = mysql_fetch_row(res);

      ss << "User[" << queryStruct.UserIdentifier << "] used a wrong pincode for room[" << queryStruct.KeyIdentifier << "].";
      Logger::debug(ss.str()); 
      
      if(atoi(row[0]) >= 5){
         userLogging(USER_BLOCKED); 
         updateUserStatus(); 
         
         ss << "User[" << queryStruct.UserIdentifier << "] is now blocked.";
         Logger::debug(ss.str());
         
         return USER_BLOCKED; 
      } else {
         userLogging(NO_ACCESS); 
         //printf("User has %u tries left \n", (5 - atoi(row[0])));
         int tries = 5 - atoi(row[0]);
         if(tries == 1){
           ss << "User[" << queryStruct.UserIdentifier << "] has " << tries << " try left.";
           Logger::debug(ss.str());   
         }else if(tries > 1){
           ss << "User[" << queryStruct.UserIdentifier << "] has " << tries << " tries left.";
           Logger::debug(ss.str()); 
         }              
         return NO_ACCESS; 
      }
      mysql_free_result(res); 
    }             
  }
  
  ss << "User[" << queryStruct.UserIdentifier << "] has no acces to room[" << queryStruct.KeyIdentifier << "].";
  Logger::debug(ss.str());
  
  return NO_ACCESS;              
}

/**
 *  Get Access Type (Look if user is a super user)
 */
bool DataBaseConnector::mysql_get_access_type(){
  int num_result = 0;
  string strResult;
  ostringstream convert;  
  char *cstr;  
  
  // Make the query
  mysql_set_query_access_rights();
  num_result = mysql_num_rows(res);
  row = mysql_fetch_row(res);
  mysql_free_result(res);
  
  // Int to char*
  convert << queryStruct.PinCode;
  strResult = convert.str();
  cstr = new char[strResult.size()];
  strcpy(cstr, strResult.c_str());
  
  if(num_result > 0){
    if((strcmp(row[0], cstr) == 0)){
      ss << "User[" << queryStruct.UserIdentifier << "] has Super Access Rights";
      Logger::debug(ss.str());        
      return true;   
    } else {
      return false; 
    }
  } else { 
    ss << "User[" << queryStruct.UserIdentifier << "] has NO Super Access Rights";
    Logger::debug(ss.str());  
    return false;
  }
}

void DataBaseConnector::updateUserStatus(){
  string s;
  stringstream out;

  out << "UPDATE user set blocked = '1' WHERE userIdentifier = '" << queryStruct.UserIdentifier << "'";
  
  s = out.str();

  char * cstr; 
  cstr = new char[s.size()+1];
  strcpy(cstr, s.c_str());
    
  res = mysql_perform_query(conn, cstr);
      
  out.str("");
  delete[] cstr;   
}

void DataBaseConnector::userLogging(ResponseAnswer theResult){
  string s;
  string str;
  stringstream out;

  str = responseAnswerConverter(theResult);
  const char *c = str.c_str();
  
  out << "INSERT INTO userLog VALUES ('" << queryStruct.UserIdentifier << "','" << queryStruct.KeyIdentifier << "'," << " NOW() " << ",'" << c << "')";
     
  s = out.str();

  char * cstr;
  cstr = new char[s.size()+1];
  strcpy(cstr, s.c_str());
    
  res = mysql_perform_query(conn, cstr);
      
  out.str("");
  delete[] cstr;  
}

string DataBaseConnector::responseAnswerConverter(ResponseAnswer theResult){    
  string theString;
  if (PERMISSION_GRANTED == theResult) {
    return theString = "PERMISSION_GRANTED";
  } else if (USER_BLOCKED == theResult){
    return theString = "USER_BLOCKED";
  } else {
    return theString = "NO_ACCESS";
  }    
}

void DataBaseConnector::countLogTries(uint32_t UserIdentifier) {   
  string s;
  stringstream out;

  out << "SELECT COUNT(*) "
         "FROM userLog WHERE logDate BETWEEN DATE_SUB(NOW(), INTERVAL 1 HOUR) AND NOW() AND result = 'NO_ACCESS' "
         "AND userIdentifier = " << UserIdentifier;
     
  s = out.str();

  char * cstr;
  cstr = new char[s.size()+1];
  strcpy(cstr, s.c_str());
  
  res = mysql_perform_query(conn, cstr);
      
  out.str("");
  delete[] cstr;
}


