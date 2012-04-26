/* 
 * File:   HanRequest.h
 * Author: stejanse
 *
 * Created on April 23, 2012, 6:11 PM
 */

#ifndef HANREQUEST_H
#define	HANREQUEST_H

#include "Defines.h"

class HanRequest {
public:
    HanRequest();
    ~HanRequest();
    
    /**
     * Set the identifier of the key sending this request frame.
     * @param keyIdentifier Key identifier.
     */
    void setKeyIdentifier(short keyIdentifier);
    
    /**
     * Set the user identifier.
     * @param userIdentifier Identifier identifing the user.
     */
    void setUserIdentifier(int userIdentifier);
    
    /**
     * Set the code used by the user to identifier him/herself.
     * @param code The code.
     */
    void setCode(short code);
    
    /**
     * Set to TRUE if this is a testFrame, FALSE (default) otherwise.
     * @param testFrame Is this a test frame?
     */
    void setTestFrame(bool testFrame);
    
    /**
     * @return TRUE if this is a testframe, FALSE otherwise.
     */
    bool isTestFrame();
    
    /**
     * Set the lock status. TRUE for locked, FALSE for not locked.
     * @param lockStatus
     */
    void setLockStatus(bool lockStatus);
    
    /**
     * @return TRUE if lock was locked while sending this request, FALSE otherwise.
     */
    bool isLocked();
    
    /**
     * @return Retrieve the frame, ready to send.
     */
    void *getFrame();
    
    /**
     * 
     * @return returns the size of the frame.
     */
    uint32_t getFrameSize();

private:
    struct {
        uint16_t keyIdentifier;
        uint32_t userIdentifier;
        uint16_t code;
        uint8_t flags;
        uint8_t data;
        uint16_t checksum;
    } frame;
    
    enum flags {
        TEST_FRAME = 0b00000001,
        INCORRECT_CHECKSUM = 0b00000010,
        UNLOCKED = 0b00000100
    };
    
    uint16_t checksum(uint16_t *buf);
};

#endif	/* HANREQUEST_H */

/*Optional getters:
 * short getCode(); 
 * short getKeyIdentifier();
 *  int getUserIdentifier();
 */ 
    
    
