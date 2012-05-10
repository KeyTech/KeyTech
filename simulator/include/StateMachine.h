/* 
 * File:   StateMachine.h
 * Author: nathanael
 *
 * Created on April 25, 2012, 10:07 AM
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include "Defines.h"
#include "LockSimulator.h"
#include "Communicate.h"
#include "HanException.h"

/*! \brief States:
 * 
 */
#define INIT 0
#define IDLE 1
#define SEND 2
#define RECEIVE 3
#define PROCESS_OUTPUT 4
#define ERROR 5
#define COMMUNICATE 6

class StateMachine {
public:
    
    /**
     * Constructor
     * @param argc the number of command line arguments entered.
     * @param argv the arguments themselves.
     */
    StateMachine(int argc, char** argv);

    /**
     * Constructor
     * @param argc the number of command line arguments entered.
     * @param argv the arguments themselves.
     * @param is is the stream to read from.
     */
    StateMachine(int argc, char** argv, istream *is);

    /** Init
    * 
    * \return True when init successful, false if it failed.
    */
    bool init();
    
    /** State Machine
     * Starts the state machine and determines the next state to be executed.
     */
    void runStateMachine();
    
private:
    Communicate *communicate;
    LockSimulator *lockSimulator;
    istream *stream;
    int next_state;
};

#endif	/* STATEMACHINE_H */

