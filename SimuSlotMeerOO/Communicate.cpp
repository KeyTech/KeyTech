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
    int sent_bytes = 0;
    char buf[request.getFrameSize()];
    size_t ser_len;
    
    request.setKeyIdentifier(lockID);
    request.setCode(code);
    request.setUserIdentifier(userID);
    ser_len = serialize((frame*) request.getFrame(), buf);
    
    cout << "Contents buf serial: " << endl;
    for(unsigned int i = 0; i<sizeof(buf); i++) {
        printf("%u", buf[i]);
    }
    cout << endl;
    
    if((sent_bytes = sendto(sd, buf, ser_len, 0, (const struct sockaddr*)sad, saddrlen)) == ser_len ) {
        cout << "Bytes sent: " << sent_bytes << endl; 
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
    char buf[response.getFrameSize()];
    
    if((recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr*)sad, &saddrlen)) < 0) {
        perror("Error while receiving"); return false;
    }
    cout << "Contents buf pre-deserial: " << endl;
    for(unsigned int i = 0; i<sizeof(buf); i++) {
        printf("%u", buf[i]);
    }
    cout << endl;
    
    deserialize((frame*) response.getFrame(), buf);
    
    cout << "Response data, lock#: " << response.getKeyIdentifier() << endl;
    
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

size_t Communicate::serialize(const frame* arch, char* buf)
{
   size_t bytes = 0;

   memcpy(buf + bytes, (const void*) &arch->flags, sizeof(arch->flags));
   bytes += sizeof(arch->flags);

   memcpy(buf + bytes, (const void*) &arch->keyIdentifier, sizeof(arch->keyIdentifier));
   bytes += sizeof(arch->keyIdentifier);
   
   memcpy(buf + bytes, (const void*) &arch->userIdentifier, sizeof(arch->userIdentifier));
   bytes += sizeof(arch->userIdentifier);
   
   memcpy(buf + bytes, (const void*) &arch->code, sizeof(arch->code));
   bytes += sizeof(arch->code);
   
   memcpy(buf + bytes, (const void*) &arch->data, sizeof(arch->data));
   bytes += sizeof(arch->data);
   
   memcpy(buf + bytes, (const void*) &arch->checksum, sizeof(arch->checksum));
   bytes += sizeof(arch->checksum);
   
   return bytes;
}


void Communicate::deserialize(frame* arch, const char* buf)
{
   size_t offset = 0;

   memcpy(&arch->flags, buf + offset, sizeof(arch->flags));
   offset += sizeof(arch->flags);

   memcpy(&arch->keyIdentifier, buf + offset, sizeof(arch->keyIdentifier));
   offset += sizeof(arch->keyIdentifier);

   memcpy(&arch->userIdentifier, buf + offset, sizeof(arch->userIdentifier));
   offset += sizeof(arch->userIdentifier);
   
   memcpy(&arch->code, buf + offset, sizeof(arch->code));
   offset += sizeof(arch->code);
   
   memcpy(&arch->data, buf + offset, sizeof(arch->data));
   offset += sizeof(arch->data);
   
   memcpy(&arch->checksum, buf + offset, sizeof(arch->checksum));
   offset += sizeof(arch->checksum);
   
}