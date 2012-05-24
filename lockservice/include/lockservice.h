/* 
 * File:   lockservice.h
 * Author: torisuta
 *
 * Created on May 16, 2012, 2:30 PM
 */

#ifndef LOCKSERVICE_H
#define	LOCKSERVICE_H

#include "communication.h"
#include "authenticator.h"
#include <iostream>

class LockService {
public:
    LockService(int argc, char** argv);
    ~LockService();
private:
   
    Communication *communicaton;
    Authenticator *authenticator;
    
};

#endif	/* LOCKSERVICE_H */

