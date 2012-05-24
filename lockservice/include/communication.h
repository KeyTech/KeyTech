/* 
 * File:   communication.h
 * Author: torisuta
 *
 * Created on May 16, 2012, 2:05 PM
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#include <string>
#include <iostream>
#include "sockets.h"
#include "han.h"
#include "HanRequest.h"
#include "HanResponse.h"
#include "HanException.h"
#include "Defines.h"

class Communication {
public:
    Communication(string serverAddress, uint16_t serverPort);
    ~Communication();
    
    bool waitForRequest();
    
    void sendResponse(ResponseAnswer flags);
    
    uint16_t getKeyIdentifier();
    
    uint32_t getUserIdentifier();
    
    uint16_t getPincode();
    
private:
    
    Sockets *client;
    
    int recvMsgSize;
    
    void sendTestResponse();
    
    struct ComStruct {
        
        string sourceAddress;
        unsigned short sourcePort;
        uint16_t KeyIdentifier;
        uint32_t UserIdentifier;
        uint16_t PinCode;
        uint8_t Flag;
        
    } queryStruct;
      
};

#endif	/* COMMUNICATION_H */

