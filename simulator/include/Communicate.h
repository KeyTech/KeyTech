/* 
 * File:   Communicate.h
 * Author: nathanael
 *
 * Created on April 25, 2012, 11:57 AM
 */

#ifndef COMMUNICATE_H
#define	COMMUNICATE_H

#include "HanRequest.h"
#include "HanResponse.h"
#include "Defines.h"

/*! \brief Request flags:
 * 
 */
#define SIT_NORM 0b00000000
#define TEST_FRAME 0b00000001
#define ERR_LOCK_CHECKSUM 0b00000010

/*! \brief Response flags:
 * 
 */
#define PERMISSION_GRANTED 0b00000001
#define ERR_ID_INCORRECT 0b00000010
#define ERR_UNAUTHORISED 0b00000100
#define ERR_BLOCKED 0b00001000
#define ERR_SERVER_CHECKSUM 0b00010000
#define TEST_FRAME_ANSWER 0b00100000

class Communicate {
public:
    
    bool sendRequest(struct sockaddr_in *sad, int sd, uint16_t lockID, uint32_t userID, uint16_t code);
    uint8_t receiveResponse(struct sockaddr_in *sad, uint32_t sd, uint16_t lockID);
};

#endif	/* COMMUNICATE_H */

