#include <string.h>
#include <arpa/inet.h>
#include <strings.h>
#include <exception>

#include "HanRequest.h"

using namespace std;

HanRequest::HanRequest() {
    bzero(&frame, sizeof(frame));
}


HanRequest::~HanRequest() {
    cout << "HanRequest has been destroyed." << endl;
}

void HanRequest::setKeyIdentifier(short keyIdentifier) {
    frame.keyIdentifier = htons(keyIdentifier);
}

void HanRequest::setUserIdentifier(int userIdentifier) {
    frame.userIdentifier = htonl(userIdentifier);
}

void HanRequest::setCode(short code) {
    frame.code = htons(code);
}

void HanRequest::setLockStatus(bool lockStatus) {
    frame.flags = 0;
}

void HanRequest::setTestFrame(bool testFrame) {
    if(testFrame) {
        frame.flags |= TEST_FRAME;        
    } else {
        frame.flags &= ~TEST_FRAME;
    }
}

void *HanRequest::getFrame() {
    frame.checksum = htons(checksum((uint16_t *)&frame));
    printf("Checksum value: %u\n", frame.checksum);
    return (void *) &frame;
}

uint32_t HanRequest::getFrameSize() {
    return sizeof(frame);
}

uint16_t HanRequest::checksum(uint16_t* buf) {
    uint16_t* temp = buf + getFrameSize() - sizeof(frame.checksum);
    int sum;
    for(sum = 0; buf < temp; buf++) {
        sum += *buf;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}