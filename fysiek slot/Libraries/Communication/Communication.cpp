/* 
Communication library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

// include core Wiring API
#include <Arduino.h>

// include this library's description file
#include "Communication.h"

// include description files for other libraries used (if any)
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Frames.h>
//DHCP variables:
//byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

//Other variables:
//IPAddress service(192, 168, 1, 5); //Service IP , Service Port: 7000

Communication::Communication()
{
	Eth = new EthernetClass();
	UDP = new EthernetUDP();
	Frame = new Frames();
}

Communication::~Communication() {}

bool Communication::initCom(uint16_t ID) {
	lockID = ID;
	// start the Ethernet connection:
	byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
	if (Ethernet.begin(mac) == 0) {
		return false;
	} else {
		UDP->begin(SERVICE_PORT);
		if(sendTestRequest()){
			return true;
		} else {
			return false;
		}
	}
}

int Communication::sendRequest(const uint32_t *userID, const uint16_t *pincode, bool lockstatus) {
	uint8_t flags = 0;
	uint8_t status = REQ_LOCK_CLOSED;
	if(lockstatus) status = REQ_LOCK_OPEN;
	studentID = *userID;
	Frame->createRequest(&lockID, userID, pincode, &flags, &status);
	//Unlike sendTestRequest this request only happens once. The network should be fine once we get to this stage.
	if(sendAndReceiveData()) {
		if((flags = Frame->getResponseFlags()) != RES_TEST_RESPONSE) {
			return flags; //Received response was indeed a proper answer.
		} else {
			 return ATTEMPT_FAILED; //Returned answer is an unexpected test frame answer.
		}
	} else {
		 return ATTEMPT_FAILED;//Sending or receiving data failed.
	}
}

bool Communication::sendTestRequest() {
	uint8_t test = REQ_TESTFRAME;
	uint32_t zero = 0;
	Frame->createRequest(&lockID, &zero, (uint16_t*) &zero, &test, (uint8_t*) &zero);
	for(int i=0; i<TRIES; i++) { //Try a couple of times to perform a test - response sequence.
		if(sendAndReceiveData()) {
			if(Frame->getResponseFlags() == RES_TEST_RESPONSE) {
				return true; //Received response was indeed a testframe response.
			} else {
				continue; //Returned answer was not a testframe response.
			}
		} else {
			continue; //Sending or receiving data failed.
		}
	}
	return false;
}

bool Communication::sendAndReceiveData() {
	int rec_bytes;
	for(int i = 0; i < TRIES; i++) {
		if(sendData()) {
			do {
				rec_bytes = UDP->parsePacket();
				delay(10);
			} while (rec_bytes < Frame->getFrameSize() ); //Wait until something has come in.
			if(receiveData()) {
				return true;
			} else {
				delay(DELAY); //Wait a while before trying again.
				continue;
			}
		} else {
			delay(DELAY); //Wait a while before trying again.
			continue;
		}
	}
	return false; //Sending and receiving failed.
}

/*If I understand the UCP header+cpp files correctly it's also possible to use a host name instead of an IP address. This
host name is converted to an IP via a DNS lookup. This should be tested for later use as it would allow us to use a completely
dynamic IP system in which only the server needs to get registered at a DNS service.*/
bool Communication::sendData() {
	IPAddress serviceIP(192,168,1,5);
	if(UDP->beginPacket(serviceIP, SERVICE_PORT)) { //1 if building packet was succesful.
		UDP->write(Frame->getRequestFrame(), Frame->getFrameSize());
		if(UDP->endPacket()) { //1 is sending has been succesful.
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Communication:: receiveData() {
	UDP->read((char*)Frame->getReponseFrame(), Frame->getFrameSize());
	if(Frame->checkResFrame()){
		if(Frame->getResponseFlags() != RES_BAD_CHECKSUM && Frame->getResponseLockID() != lockID && Frame->getResponseUserID() != studentID) {
			return true;
		} else {
			return false; //Checksum, lockID or userID in response from service failed. Resend the frame.
		}
	} else {
//Checksum incorrect, got to ask again. Question: should the incorrect checksum flag be set or should the whole request just be remade?
		//Right now, by returning a false the whole frame is resend without setting the checksum flag.
		return false;
	}
}