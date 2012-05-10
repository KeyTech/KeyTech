#ifndef SLOTIO_H
#define	SLOTIO_H

#include "Defines.h"


class LockSimulator {
public:

	/**
	 * Constructor.
	 * @param is is the stream to read from.
	 */
	LockSimulator(istream *is);

	/**
    * Constructor.
	*/
	LockSimulator();

    /**
     * Processes the input given by users.
     * @return next_state Returns the next state to be executed by the state machine.
     */
    bool detectEntry();
    
    /**
     * Turns the response packets into orders.
     * @param flags A pointer to the response packet generated by the Communication class.
     * @return returns true for any known answers, false if not.
     */
    bool setOutput(ResponseAnswer flags);
    
    /**
     * brief Sets the door state.
     * @param state The state to set the door to. Either OPEN or CLOSED.
     */
    void SetDoorState(bool state);
    
    /**
     * Returns the state of the door.
     * @return Returns the state of the door. Either OPEN or CLOSED.
     */
    bool GetDoorState();
    
    /**
     * Getter for the student ID.
     * Allows another class to get the ID input by the user.
     * @return returns the student ID in a 32 bit unsigned int.
     */
    uint32_t getStudentId();
    
    /**
     * Getter for the pin
     * Allows another class to get the pin input by the user.
     * @return returns the pin in a 16 bit unsigned int.
     */
    uint16_t getPin();
    
    
/**
 * A macro to flush the input from the command line.
 * Macro om stdin te flushen.
 http://www.daniweb.com/software-development/c/code/217396
 */
char Junk[16]; // buffer for discarding excessive user input, used by "FLUSH_STDIN" macro
#define FLUSH_STDIN(x) {if(x[strlen(x)-1]!='\n'){do fgets(Junk,16,stdin);while(Junk[strlen(Junk)-1]!='\n');}else x[strlen(x)-1]='\0';}
    
private:
    uint32_t studentID;
    uint16_t pin;
    bool door_state;
    istream *stream;
};

#endif	/* SLOTIO_H */

