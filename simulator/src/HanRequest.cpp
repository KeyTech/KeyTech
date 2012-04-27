#include <string.h>
#include <arpa/inet.h>
#include <strings.h>
#include <exception>

#include "HanRequest.h"

using namespace std;

HanRequest::HanRequest() : HanFrame() {}


uint16_t HanRequest::getKeyIdentifier() {
    return ntohs((uint16_t) frame[KEY_IDENTIFIER]);
}

void HanRequest::setKeyIdentifier(uint16_t keyIdentifier) {
    uint16_t *location = (uint16_t *) &frame[KEY_IDENTIFIER];
    *location = htons(keyIdentifier);
}

uint32_t HanRequest::getUserIdentifier() {
    return ntohl((uint32_t) frame[USER_IDENTIFIER]);
}

void HanRequest::setUserIdentifier(uint32_t userIdentifier) {
    uint32_t *location = (uint32_t *) &frame[USER_IDENTIFIER];
    *location = htonl(userIdentifier);
}

void HanRequest::setCode(uint16_t code) {
    uint16_t *location = (uint16_t *) &frame[PINCODE];
    *location = htons(code);
}

void HanRequest::setLockStatus(bool lockStatus) {
    //TODO
}

void HanRequest::setTestFrame(bool testFrame) {
    if(testFrame) {
        frame[FLAGS] |= TEST_FRAME;
    } else {
        frame[FLAGS] &= ~TEST_FRAME;
    }
}
