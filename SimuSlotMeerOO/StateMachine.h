/* 
 * File:   StateMachine.h
 * Author: nathanael
 *
 * Created on April 25, 2012, 10:07 AM
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include "Defines.h"
#include "HanResponse.h"
#include "SlotIO.h"
#include "Communicate.h"

/*! \brief States:
 * 
 */
#define INIT 0
#define IDLE 1
#define SEND 2
#define RECEIVE 3
#define PROCESS_OUTPUT 4
#define ERROR 5

class StateMachine {
public:
    
    /**
     * Constructor
     * @param argc the number of command line arguments entered.
     * @param argv the arguments themselves.
     */
    StateMachine(int argc, char** argv);

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
    Communicate communicate;
    SlotIO slotIO;
    
    int next_state;
    struct sockaddr_in saddr;
    int sockfd;
    int lockID;

};

#endif	/* STATEMACHINE_H */

