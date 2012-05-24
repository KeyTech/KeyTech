#include "lockservice.h"

LockService::LockService(int argc, char** argv){
    
  communicaton = new Communication(argv[1], (uint16_t) atoi(argv[2]));
  
  authenticator = new Authenticator();
    
  for(;;){   
    cout << "Waiting for data... \n" << endl;
    if(communicaton->waitForRequest()) {
      communicaton->sendResponse(authenticator->authenticate(communicaton->getKeyIdentifier(), communicaton->getUserIdentifier(), communicaton->getPincode()));
    }  
  }
}

LockService::~LockService() {
}


