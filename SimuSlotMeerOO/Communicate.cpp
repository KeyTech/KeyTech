/* 
 * File:   Communicate.cpp
 * Author: nathanael
 * 
 * Created on April 25, 2012, 11:57 AM
 */

#include "Communicate.h"

Communicate::Communicate() {
}

Communicate::~Communicate() {
}

bool Communicate::sendRequest(struct sockaddr_in *sad, int sd, uint16_t lockID, uint32_t userID, uint16_t code) {
    HanRequest request;
    socklen_t saddrlen = sizeof(struct sockaddr_in);
    
    request.setKeyIdentifier(lockID);
    request.setCode(code);
    request.setUserIdentifier(userID);
    //printf("Size of frame: %i\n", request.getFrameSize() );
    if((sendto(sd, request.getFrame(), request.getFrameSize(), 0, (const struct sockaddr*)sad, saddrlen)) == request.getFrameSize() ) {
         return true;
    } else {
        perror("Error while sending");
        return false;
    }
}

uint8_t Communicate::receiveResponse(struct sockaddr_in *sad, uint32_t sd, uint16_t lockID) {
    HanResponse response;
    socklen_t saddrlen = sizeof(struct sockaddr_in);
    uint8_t rec_flags = 0;
    if((recvfrom(sd,response.getFrame(), response.getFrameSize(), 0, (struct sockaddr*)sad, &saddrlen)) < 0) {
        perror("Error while receiving"); return false;                                                                }
    
    // check if the checksum is correct
    if(response.checksumOK() )  {
        cout << "Checksum ok!\n";
    } else  { 
        cout << "Error: bad checksum\n";
        return rec_flags;
    }
    
    // check of the lock number is correct
    if(response.getKeyIdentifier() == lockID)   {
        cout << "Lock number ok!\n";
    } else  {
        cout << "Error: wrong lock number\n";
        return rec_flags;
    } 
    rec_flags = response.getFlags();
    printf("received lock nr: %u\n", response.getKeyIdentifier());
    printf("received flags: %u\n", rec_flags);
    printf("received user id: %d\n", response.getUserIdentifier());
    
    return rec_flags;
}