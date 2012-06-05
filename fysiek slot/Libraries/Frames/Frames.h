/* 
Frames library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

#ifndef FRAME_H
#define FRAME_H

#include <Arduino.h>

//General frame defines:
#define CHECKSUM 10
#define FRAME_SIZE 12
#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 2
//Request defines:
#define REQ_LOCK_ID 0
#define REQ_USER_ID 2
#define REQ_PINCODE 6
#define REQ_FLAGS 8
#define REQ_DATA 9
//Response defines:
#define RES_LOCK_ID 0
#define RES_USER_ID 2
#define RES_FLAGS 6

class Frames
{
  public:
	Frames();
	~Frames();
	//Request:
	/** Takes the variables given and creates a request frame complete with checksum.
	* @param *lockID const pointer to lockID
	* @param *userID const pointer to userID
	* @param *pincode const pointer to pincode
	* @param *flags const pointer to flags
	* @param *data const pointer to data
	* @return returns a pointer to the filled request frame.
	*/
	void createRequest(const uint16_t *lockID, const uint32_t *userID, const uint16_t *pincode, const uint8_t *flags, const uint8_t *data); //using const* to limit copy actions.

	//Response:
	/** Checks if the response frame has a good checksum.
	*/
	bool checkResFrame();
	/**
	* @return returns the lockID sent by the service.
	*/
	uint16_t getResponseLockID();
	/**
	* @return returns the userID sent by the service.
	*/
	uint32_t getResponseUserID();
	/**
	* @return returns the flags sent by the service.
	*/
	uint8_t getResponseFlags();

	//Other:
	/**
	* @return returns a pointer to the response frame.
	*/
	uint8_t* getReponseFrame();
	/**
	* @return returns a pointer to the request frame.
	*/
	uint8_t* getRequestFrame();

	/**
	* @return returns the size of the frame.
	*/
	int getFrameSize();

  private:
	void emptyFrame(void *framebuffer, int size);
	//Request private setters:
	void setReqLockID(const uint16_t *lockID);
	void setReqUserID(const uint32_t *userID);
	void setReqPin(const uint16_t *pincode);
	void setReqFlags(const uint8_t *flags);
	void setReqData(const uint8_t *data);

	uint32_t ntohl(uint32_t x);
	uint32_t htonl(uint32_t x);
	uint16_t ntohs(uint16_t x);
	uint16_t htons(uint16_t x);

	//Other:
	uint16_t calculateChecksum(uint8_t *framebuffer);

	uint8_t request[FRAME_SIZE];
	uint8_t response[FRAME_SIZE];
	uint8_t byte_order;
};

#endif //FRAME_H