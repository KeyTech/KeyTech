/* 
 * File:   HanRequest.h
 * Author: stejanse
 *
 * Created on April 23, 2012, 6:11 PM
 */

#ifndef HANREQUEST_H
#define	HANREQUEST_H

class HanRequest {
public:
    HanRequest();
    
    /**
     * Set the identifier of the key sending this request frame.
     * @param keyIdentifier Key identifier.
     */
    void setKeyIdentifier(short keyIdentifier);
    
    /**
     * @return The identifier of the key sending this frame.
     */
    short getKeyIdentifier();
    
    /**
     * Set the user identifier.
     * @param userIdentifier Identifier identifing the user.
     */
    void setUserIdentifier(int userIdentifier);
    
    /**
     * @return The user identifier.
     */
    int getUserIdentifier();
    
    /**
     * Set the code used by the user to identifier him/herself.
     * @param code The code.
     */
    void setCode(short code);
    
    /**
     * @return Retrieve the code used by the user to identify himself.
     */
    short getCode();
    
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

private:
    struct {
        unsigned short keyIdentifier;
        unsigned short checksum;
        unsigned int userIdentifier;
        unsigned short code;
        unsigned char flags;
        unsigned char data;
    } frame;
    
    enum flags {
        TEST_FRAME = 0b00000001,
        INCORRECT_CHECKSUM = 0b00000010,
        UNLOCKED = 0b00000100
    };
};

#endif	/* HANREQUEST_H */

