/* 
 * File:   StateMachine.cpp
 * Author: nathanael
 * 
 * Created on April 25, 2012, 10:07 AM
 */

#include "StateMachine.h"

StateMachine::StateMachine(int argc, char** argv)
: next_state(INIT)
{
	cout << "FSM state : " << next_state;
    cout << "State Machine started." << endl;
    
    try {
        communicate = new Communicate(argv[1], (uint16_t) atoi(argv[2]), (uint16_t) atoi(argv[3]) );
    } catch (HanException ex) {
        ex.getMessage();
        exit(EXIT_FAILURE);
    }
    lockSimulator = new LockSimulator();
}

bool StateMachine::init() {
    //SlotIO:
	lockSimulator->SetDoorState(OPEN);
    if(communicate->sendTestRequest()){
        return true;
    } else {
        return false;
    }
}

void StateMachine::runStateMachine() {
    ResponseAnswer answer;
    while(true){
        //cout << "Next_state: " << next_state << endl;
        switch(next_state){
            case IDLE:
                cout << "Test state IDLE" << endl;
                if(lockSimulator->detectEntry()){
                    next_state = SEND;
                } else {
                    next_state = IDLE;
                }
                break;
            case COMMUNICATE:
                try {
                    answer = communicate->sendRequest();
                    next_state = PROCESS_OUTPUT;
                } catch (HanException ex) {
                    next_state = ERROR;
                    ex.getMessage();
                }
                break;
            case PROCESS_OUTPUT:
                cout << "Test state PROCESS_OUTPUT" << endl;
                if(lockSimulator->setOutput(answer) ) {
                    next_state = IDLE;
                } else {
                    next_state = SEND;
                }
                next_state = IDLE;
                break;
            case ERROR:
                cout << "Error state" << endl;
                next_state = INIT;
                break;
            case INIT:
                if(init()){
                    next_state = IDLE;
                } else {
                    next_state = INIT;
                }
                break;
            default:
                cerr << "No valid state selected" << endl << "Exiting program" << endl;
                exit(0);
        }
    }
}

