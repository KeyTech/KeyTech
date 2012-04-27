/* 
 * File:   HasResponse.h
 * Author: hanna
 *
 * Created on April 23, 2012, 10:50 AM
 */

#ifndef HANRESPONSE_H
#define	HANRESPONSE_H

#include "Defines.h"

class HanResponse {

public:
    HanResponse();
    ~HanResponse();
    
    /**
     * @return The identifier of the key sending this frame.
     */
    uint16_t getKeyIdentifier();
    
    /**
     * @return The user identifier.
     */
    uint32_t getUserIdentifier();
    
    /**
     * 
     * @return returns the flags of the frame
     */
    uint8_t getFlags();
    
//    /**
//     * 
//     * @return returns the checksum of the frame 
//     */
//    uint16_t getChecksum();
    
    /**
     * @return Retrieve the frame, ready to inspect.
     */
    bool checksumOK();
    
    /**
     * @return Retrieve the frame, ready to receive.
     */
    void *getFrame();
    
    /**
     * 
     * @return returns the size of the frame.
     */
    uint32_t getFrameSize();
    
    
    
private:
     struct {
        uint8_t flags;
        uint16_t keyIdentifier;
        uint32_t userIdentifier;
        uint16_t code;
        uint8_t data;
        uint16_t checksum;
    } frame;
    
    enum flags {
        PERMISSION_GRANTED = 0b00000001,
        INCORRECT_ID = 0b00000010,
        NO_ACCESS = 0b00000100,
        USER_BLOCKED = 0b00010000,
        BAD_CHECKSUM = 0b00100000,
        TEST_RESPONSE = 0b01000000
    };
    
    uint16_t checksum(uint16_t *buf);
    uint16_t getFrameLengthWithoutChecksumField();
};

#endif	/* HASRESPONSE_H */

