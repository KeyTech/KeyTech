/* 
Frames library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

// include core Wiring API
#include <Arduino.h>

// include this library's description file
#include "Frames.h"

// include description files for other libraries used (if any)
//#include <string.h>

Frames::Frames()
{
	emptyFrame(request, sizeof(request));
	emptyFrame(response, sizeof(response));
	byte_order = LITTLE_ENDIAN;
}

Frames::~Frames() {}

void Frames::emptyFrame(void *framebuffer, int size) {
	memset(framebuffer, 0, size);
}

uint8_t* Frames::getReponseFrame() {
	return response;
}

uint8_t* Frames::getRequestFrame() {
	return request;
}

int Frames::getFrameSize() {
	return FRAME_SIZE;
}

bool Frames::checkResFrame() {
	uint16_t *location = (uint16_t *) &response[CHECKSUM];
	if(*location != calculateChecksum(response)){
		return false;
	} else {
		return true;
	}
}

void Frames::createRequest(const uint16_t *lockID, const uint32_t *userID, const uint16_t *pincode, const uint8_t *flags, const uint8_t *data) {
	emptyFrame(request, sizeof(request));
	setReqLockID(lockID);
	setReqUserID(userID);
	setReqPin(pincode);
	setReqFlags(flags);
	setReqData(data);
	uint16_t *location = (uint16_t *) &request[CHECKSUM];
	*location = calculateChecksum(request);
}

void Frames::setReqLockID(const uint16_t *lockID) {
	uint16_t *ptr = (uint16_t*) &request[REQ_LOCK_ID];
	*ptr = htons(*lockID);
}

void Frames::setReqUserID(const uint32_t *userID) {
	uint32_t *ptr = (uint32_t*) &request[REQ_USER_ID];
	*ptr = htonl(*userID);
}

void Frames::setReqPin(const uint16_t *pincode) {
	uint16_t *ptr = (uint16_t*) &request[REQ_PINCODE];
	*ptr = htons(*pincode);
}

void Frames::setReqFlags(const uint8_t *flags) {
	uint8_t *ptr = (uint8_t*) &request[REQ_FLAGS];
	*ptr = *flags;
}

void Frames::setReqData(const uint8_t *data) {
	uint8_t *ptr = (uint8_t*) &request[REQ_DATA];
	*ptr = *data;
}

uint16_t Frames::getResponseLockID() {
	uint16_t *ptr = (uint16_t*) &response[RES_LOCK_ID];
	return ntohs(*ptr);
}

uint32_t Frames::getResponseUserID() {
	uint32_t *ptr = (uint32_t*) &response[RES_USER_ID];
	return ntohl(*ptr);
}

uint8_t Frames::getResponseFlags() {
	/*uint8_t *ptr = (uint8_t*) &framebuffer[RES_FLAGS];
	return *ptr;*/
	return response[RES_FLAGS];
}

uint16_t Frames::calculateChecksum(uint8_t *framebuffer) {
	uint16_t checksum = 0;
	unsigned int i;

	for (i = 0; i < CHECKSUM; i += sizeof(uint16_t)) {
		uint16_t *temp = (uint16_t *) &framebuffer[i];
		checksum ^= *temp;
	}

	checksum = ntohs(checksum);
	return htons((checksum >> 8) | ~((uint8_t) checksum) << 8);

}

uint32_t Frames::ntohl(uint32_t x) {
	if(byte_order == LITTLE_ENDIAN) {
		//uint8_t *s = (uint8_t *)&x;
		//return (uint32_t)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
		return (((x&0x000000FF)<<24)+((x&0x0000FF00)<<8)+
		((x&0x00FF0000)>>8)+((x&0xFF000000)>>24));
	} else {
		return x;
	}
}

uint32_t Frames::htonl(uint32_t x) {
	if(byte_order == LITTLE_ENDIAN) {
		return (((x&0x000000FF)<<24)+((x&0x0000FF00)<<8)+
		((x&0x00FF0000)>>8)+((x&0xFF000000)>>24));
	} else {
		return x;
	}	
}

uint16_t Frames::ntohs(uint16_t x) {
	if(byte_order == LITTLE_ENDIAN) {
		//uint8_t *s = (uint8_t *) &x;
		//return (uint16_t)(s[0] << 8 | s[1]);
		return (((x>> 8)) | (x << 8));
	} else {
		return x;
	}
}

uint16_t Frames::htons(uint16_t x) {
	if(byte_order == LITTLE_ENDIAN) {
		return (((x>> 8)) | (x << 8));
	} else {
		return x;
	}
}
