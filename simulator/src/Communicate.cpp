#include "Communicate.h"

bool Communicate::sendRequest(struct sockaddr_in *serverAddress, int socketDescriptor, uint16_t lockID, uint32_t userID, uint16_t code) {
    HanRequest request;
    int sent_bytes = 0;
    void *buffer;
    
    request.setKeyIdentifier(lockID);
    request.setCode(code);
    request.setUserIdentifier(userID);
    
    buffer = request.getFrame();
    
    if((sent_bytes = sendto(socketDescriptor, buffer, request.getFrameSize(), 0, (const struct sockaddr*)serverAddress, sizeof(struct sockaddr_in))) == request.getFrameSize()) {
        cout << "Bytes sent: " << sent_bytes << endl; 
        return true;
    } else {
        perror("Error while sending");
        return false;
    }
}

uint8_t Communicate::receiveResponse(struct sockaddr_in *serverAddress, uint32_t sd, uint16_t lockID) {
    HanResponse response;
    socklen_t addressLength = sizeof(struct sockaddr_in);
    uint8_t rec_flags = 0;
    char buffer[response.getFrameSize()];
    
    if((recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)serverAddress, &addressLength)) < 0) {
        perror("Error while receiving"); return false;
    }
    
    response.setFrame(buffer);

    cout << "Response data, lock#: " << (short) buffer[1] << response.getKeyIdentifier() << endl;

    // check if the checksum is correct
    if(response.checkChecksum() )  {
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
    //rec_flags = response.getFlags();
    printf("received lock nr: %u\n", response.getKeyIdentifier());
    printf("received user id: %d\n", response.getUserIdentifier());
    
    return rec_flags;
}
