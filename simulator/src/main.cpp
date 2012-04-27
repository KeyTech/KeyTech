/* 
 * File:   main.cpp
 * Author: nathanael
 *
 * Created on April 23, 2012, 12:55 PM
 */

#include "Defines.h"
#include "StateMachine.h"

/*! \brief SimuSlot main to be executed at start up.
 * This main creates all the necessary variables as well as executes the state machine.
 * \param argc The number of command line arguments.
 * \param argv The contents of the command line arguments.
 * \return exit_state this function should never return as the state machine can't be shutdown. 
 */
int main(int argc, char** argv) {
    StateMachine stateMachine(argc, argv);
    stateMachine.runStateMachine();

    return 0;
}
