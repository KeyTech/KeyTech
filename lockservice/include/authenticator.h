/* 
 * File:   authenticator.h
 * Author: tristan
 *
 * Created on May 20, 2012, 10:45 PM
 */

#ifndef AUTHENTICATOR_H
#define	AUTHENTICATOR_H

#include "DataBaseConnector.h"
#include "Defines.h"

class Authenticator {
public:
    Authenticator();
    ~Authenticator();
    
    ResponseAnswer authenticate(uint16_t KeyIdentifier, uint32_t UserIdentifier, uint16_t Pincode);
    
private:

};

#endif	/* AUTHENTICATOR_H */

