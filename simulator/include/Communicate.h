#ifndef COMMUNICATE_H
#define	COMMUNICATE_H

#include <sys/socket.h>
#include "HanRequest.h"
#include "HanResponse.h"
#include "HanException.h"
#include "Defines.h"

class Communicate {
public:
    Communicate(string serverAddress, uint16_t port, uint16_t lockIdentifier) throw (HanException);
    
    ResponseAnswer sendRequest(uint32_t userIdentifier, uint16_t pincode) throw (HanException);
    bool sendTestRequest();
    
private:
    sockaddr_in serverAddress;
    uint16_t lockIdentifier;
    int socketDescriptor;
};

#endif	/* COMMUNICATE_H */

