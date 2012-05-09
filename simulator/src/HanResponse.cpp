#include <stdint.h>
#include <arpa/inet.h>
#include "HanResponse.h"
#include "Defines.h"

HanResponse::HanResponse() : HanFrame() {}

uint16_t HanResponse::getKeyIdentifier() {
	uint16_t *keyIdentifier = (uint16_t *) &frame[KEY_IDENTIFIER];
	return ntohs(*keyIdentifier);
}

void HanResponse::setKeyIdentifier(uint16_t keyIdentifier) {
	uint16_t *location = (uint16_t *) &frame[KEY_IDENTIFIER];
	*location = htons(keyIdentifier);
}

uint32_t HanResponse::getUserIdentifier() {
	uint32_t *userIdentifier = (uint32_t *) &frame[USER_IDENTIFIER];
	return ntohl(*userIdentifier);
}

void HanResponse::setUserIdentifier(uint32_t userIdentifier) {
	uint32_t *location = (uint32_t *) &frame[USER_IDENTIFIER];
	*location = htonl(userIdentifier);
}

void HanResponse::setAnswer(ResponseAnswer answer) {
	frame[FLAGS] &= ~(F_PERMISSION_GRANTED | F_INCORRECT_ID | F_NO_ACCESS
			| F_USER_BLOCKED);
	switch (answer) {
		case INCORRECT_ID:
			frame[FLAGS] |= F_INCORRECT_ID;
			break;
		case NO_ACCESS:
			frame[FLAGS] |= F_NO_ACCESS;
			break;
		case USER_BLOCKED:
			frame[FLAGS] |= F_USER_BLOCKED;
			break;
		default:
			frame[FLAGS] |= F_PERMISSION_GRANTED;
			break;
	}
}

ResponseAnswer HanResponse::getAnswer() {
	if (frame[FLAGS] & F_PERMISSION_GRANTED) {
		return PERMISSION_GRANTED;
	}
}

bool HanResponse::isTestFrameAnswer() {
	return (frame[FLAGS] & F_TEST_RESPONSE);
}

void HanResponse::setTestFrameAnswer(bool testFrameAnswer) {
	if (testFrameAnswer) {
		frame[FLAGS] |= F_TEST_RESPONSE;
	} else {
		frame[FLAGS] &= ~F_TEST_RESPONSE;
	}
}

bool HanResponse::checkChecksum() {
	uint16_t *checksum = (uint16_t *) &frame[CHECKSUM];
	if (*checksum == calculateChecksum()) {
		return true;
	}
	return false;
}
