#include <strings.h>
#include <arpa/inet.h>

#include "HanFrame.h"

HanFrame::HanFrame() {
    bzero(&frame, sizeof (frame));
}

void *HanFrame::getFrame() {
    uint16_t *location = (uint16_t *) &frame[CHECKSUM];
    *location = calculateChecksum();
    return (void *) &frame;
}

int HanFrame::getFrameSize() {
    return sizeof (frame);
}

uint16_t HanFrame::calculateChecksum() {
    uint16_t checksum = 0;
    unsigned int i;

    for (i = 0; i < CHECKSUM; i += sizeof(uint16_t)) {
    	uint16_t *temp = (uint16_t *) &frame[i];
        checksum ^= *temp;
    }

    checksum = ntohs(checksum);
    return htons((checksum >> 8) | ~((uint8_t) checksum) << 8);
}
