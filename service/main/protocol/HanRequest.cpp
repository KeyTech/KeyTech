#include <string.h>
#include <arpa/inet.h>
#include <strings.h>
#include <exception>

#include "protocol/HanRequest.h"

using namespace std;

HanRequest::HanRequest() {
    bzero(&frame, sizeof(frame));
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
    return (void *) &frame;
}