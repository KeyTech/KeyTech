#include "lockservice.h"

LockService::LockService(int argc, char** argv){
    
  communicaton = new Communication(argv[1], (uint16_t) atoi(argv[2]));
  
  authenticator = new Authenticator();
    
  for(;;){      
    ss << "Waiting for data...";
    Logger::info(ss.str());
    ss.str("");
    if(communicaton->waitForRequest()) {
      communicaton->sendResponse(authenticator->authenticate(communicaton->getKeyIdentifier(), communicaton->getUserIdentifier(), communicaton->getPincode()));
    }  
  }
}

LockService::~LockService() {
}


