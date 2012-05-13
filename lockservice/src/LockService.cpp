/* 
 * File:   LockService.cpp
 * Author: torisuta
 * 
 * Created on May 14, 2012, 11:59 AM
 */

#include "LockService.h"

LockService::LockService() throw(ErrorHandling){
    
  // if (argc < 2) {                  // Test for correct number of parameters
  //  cerr << "Usage: " <<  argv[0]  << " <IP Number> " << argv[1] << " <Server Port>" << endl;
  //  exit(1);
  //}
  
  try {
   
  unsigned short serverPort = atoi("7000");
      
  UDPSocket sock("127.0.0.1", serverPort);  
    
  dbconnector appelmoes;
      
  char comBuffer[MAXBUFSIZE];
  int recvMsgSize;
  string sourceAddress;
  unsigned short sourcePort;
    
  for(;;){
      
    appelmoes.mysql_get_query();
         
    cout << "Waiting for connection... \n\n " << endl;
    //Block until receive message from a lock
        
    recvMsgSize = sock.recvFrom(comBuffer, MAXBUFSIZE, sourceAddress, sourcePort);
          
    cout << "Received packet from " << sourceAddress << ":" << sourcePort << " message= " << comBuffer << endl;
          
    sock.sendTo(comBuffer, recvMsgSize, sourceAddress, sourcePort);  
        
  }
  }catch (ErrorHandling &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

LockService::~LockService() {
}

