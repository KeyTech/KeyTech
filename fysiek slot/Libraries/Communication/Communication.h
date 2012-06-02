/* 
Frames library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>

//Request defines:
#define REQ_TESTFRAME B00000001
#define REQ_INCORRECT_CHECKSUM B00000010
#define REQ_LOCK_OPEN B00000100
#define REQ_LOCK_CLOSED 0
//Response defines:
#define RES_PERMISSION_GRANTED B00000001
#define RES_INCORRECT_ID B00000010
#define RES_NO_ACCESS B00000100
#define RES_USER_BLOCKED B00010000
#define RES_BAD_CHECKSUM B00100000
#define RES_TEST_RESPONSE B01000000

//Com defines:
#define DELAY 1000 //Wait 1000 milliseconds.
#define BAUD_RATE 9600
#define LOCAL_PORT 8888
#define TRIES 3
#define SERVICE_PORT 7000
#define ATTEMPT_FAILED 0

class EthernetClass;
class EthernetUDP;
class Frames;

class Communication
{
public:
	Communication(); //Constructor
	~Communication();
	
	bool initCom(uint16_t ID);
	int sendRequest(const uint32_t *userID, const uint16_t *pincode, bool lockstatus);
	
private:
	bool sendTestRequest();
	bool sendData();
	//Writes the received data into the response buffer from Frames.
	bool receiveData();
	bool sendAndReceiveData();

	EthernetClass *Eth;
	EthernetUDP *UDP;
	Frames *Frame;
	uint8_t *request;
	uint16_t lockID;
	uint32_t studentID;
};

#endif //COMMUNICATION_H