/* 
 * File:   HanRequest.h
 * Author: stejanse
 *
 * Created on April 23, 2012, 6:11 PM
 */

#ifndef HANREQUEST_H
#define	HANREQUEST_H

#include "Defines.h"
#include "HanFrame.h"

class HanRequest : public HanFrame {
public:
    HanRequest();
    
    /**
     * Set the identifier of the key sending this request frame.
     * @param keyIdentifier Key identifier.
     */
    void setKeyIdentifier(uint16_t keyIdentifier);
    
    uint16_t getKeyIdentifier();

    /**
     * Set the user identifier.
     * @param userIdentifier Identifier identifing the user.
     */
    void setUserIdentifier(uint32_t userIdentifier);
    
    uint32_t getUserIdentifier();

    /**
     * Set the code used by the user to identifier him/herself.
     * @param code The code.
     */
    void setCode(uint16_t code);
    
    uint16_t getCode();

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

private:
    enum responseDefinition {
        KEY_IDENTIFIER = 0,
        USER_IDENTIFIER = 2,
        PINCODE = 6,
        FLAGS = 8,
    };

    enum flags {
        TEST_FRAME = 0b00000001,
        INCORRECT_CHECKSUM = 0b00000010,
        LOCKED = 0b00000100
    };
};

#endif	/* HANREQUEST_H */

/*Optional getters:
 * short getCode(); 
 * short getKeyIdentifier();
 *  int getUserIdentifier();
 */ 
    
    
