#ifndef COMMUNICATE_H
#define	COMMUNICATE_H

#include <sys/socket.h>
#include "HanRequest.h"
#include "HanResponse.h"
#include "HanException.h"
#include "Defines.h"
#include "UdpClient.h"

#define RETRIES 3
#define TIMEOUT 3

class Communicate {
public:
    Communicate(string serverAddress, uint16_t port, uint16_t lockIdentifier) throw (HanException);
    
    ResponseAnswer sendRequest(uint32_t userIdentifier, uint16_t pincode) throw (HanException);
    bool sendTestRequest();
    
private:
    void sendData(HanRequest request) throw(HanException);
    void receiveData(HanResponse response) throw(HanException);
    void sendAndReceiveData(HanRequest request, HanResponse response) throw (HanException);

    UdpClient *client;

    sockaddr_in serverAddress;
    uint16_t lockIdentifier;
    int socketDescriptor;
};

#endif	/* COMMUNICATE_H */

