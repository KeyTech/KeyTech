#ifndef HANRESPONSE_H
#define	HANRESPONSE_H

using namespace std;

#include "Defines.h"
#include "HanFrame.h"

class HanResponse : public HanFrame {

public:
	HanResponse();
    
    /**
     * @return The identifier of the key sending this frame.
     */
    uint16_t getKeyIdentifier();
    
    /**
     * Set the key identifier.
     * @param keyIdentifier Key identifier.
     */
    void setKeyIdentifier(uint16_t keyIdentifier);

    /**
     * @return The user identifier.
     */
    uint32_t getUserIdentifier();
    
    /**
     * Set the user identifier.
     * @param userIdentifier User identifier.
     */
    void setUserIdentifier(uint32_t userIdentifier);
    
    
    /**
     * Is this frame an answer to a test frame?
     * @return TRUE if answer to test frame, FALSE otherwise.
     */
    bool isTestFrameAnswer();

    /**
     * Is this an answer to a test frame?
     * @param testFrameAnswer TRUE if an answer to a test frame, FALSE otherwise.
     */
    void setTestFrameAnswer(bool testFrameAnswer);

    /**
     * Get the answer this frame contains.
     * @return The answer.
     * @see ResponseAnswer
     */
    ResponseAnswer getAnswer();

    /**
     * Set the answer this frame contains.
     * @param answer The answer.
     * @see ResponseAnswer
     */
    void setAnswer(ResponseAnswer answer);

    /**
     * @deprecated
     */
    bool checkChecksum();

private:
    enum responseDefinition {
        KEY_IDENTIFIER = 0,
        USER_IDENTIFIER = 2,
        FLAGS = 6,
    };
    
    enum flags {
        F_PERMISSION_GRANTED = 0b00000001,
        F_INCORRECT_ID = 0b00000010,
        F_NO_ACCESS = 0b00000100,
        F_USER_BLOCKED = 0b00010000,
        F_BAD_CHECKSUM = 0b00100000,
        F_TEST_RESPONSE = 0b01000000
    };
};

#endif	/* HASRESPONSE_H */
