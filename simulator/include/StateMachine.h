#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include "Defines.h"
#include "LockSimulator.h"
#include "Communicate.h"
#include "HanException.h"

#define INIT 0
#define IDLE 1
#define RECEIVE 2
#define PROCESS_OUTPUT 3
#define ERROR 4
#define COMMUNICATE 5

class StateMachine {
public:
    
    /**
     * @param argc the number of command line arguments entered.
     * @param argv the arguments themselves.
     */
    StateMachine(int argc, char** argv);

    /**
     * Starts the state machine and determines the next state to be executed.
     */
    void runStateMachine();
    
    /**
     * Should be called when the program tries to interrupt.
     * @return true if the state machine will interrupt, false otherwise.
     */
    bool interruptHandler();
private:
    Communicate *communicate;
    LockSimulator *lockSimulator;
    
    int state;

    int init();
    int error();
};

#endif	/* STATEMACHINE_H */
