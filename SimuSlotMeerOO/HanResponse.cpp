/* 
 * File:   HanResponse.cpp
 * Author: hanna
 * 
 * Created on April 23, 2012, 10:50 AM
 */

#include "HanResponse.h"

HanResponse::HanResponse() {
     bzero(&frame, sizeof(frame));
}

HanResponse::~HanResponse() {
    cout << "HanResponse has been destroyed." << endl;
}

uint16_t HanResponse::getKeyIdentifier() {
    return ntohs(frame.keyIdentifier);
}

uint32_t HanResponse::getUserIdentifier() {
    return ntohl(frame.userIdentifier);
}

uint8_t HanResponse::getFlags()  {
    return frame.flags;
}

//uint16_t HanResponse::getChecksum()  {
//    return ntohs(frame.checksum);
//}

void * HanResponse::getFrame()    {
    return (void *) &frame;
}

uint32_t HanResponse::getFrameSize() {
    return sizeof(frame);
}

bool HanResponse::checksumOK() {   
    //printf("response checksum: %u\n", theChecksum);
    if (frame.checksum == ntohs(checksum((uint16_t *)&frame))) {
        return true;
    }
    return false;
}

uint16_t HanResponse::getFrameLengthWithoutChecksumField() {
    return sizeof(frame.flags) + sizeof(frame.keyIdentifier)
            + sizeof(frame.userIdentifier) + sizeof(frame.code) + sizeof(frame.data)
            - sizeof(frame.checksum);
}

uint16_t HanResponse::checksum(uint16_t* buf) {
    uint16_t* temp = buf + getFrameLengthWithoutChecksumField();
    uint16_t sum;
    for(sum = 0; buf < temp; buf++) {
        sum += *buf;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

