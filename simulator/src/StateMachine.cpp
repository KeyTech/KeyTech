#include <signal.h>
#include <unistd.h>

#include "Logger.h"
#include "StateMachine.h"

StateMachine::StateMachine(int argc, char** argv)
: state(INIT)
{
    try {
        communicate = new Communicate(argv[1], (uint16_t) atoi(argv[2]), (uint16_t) atoi(argv[3]));
    } catch (HanException& ex) {
        cout << ex.getMessage();
        exit(EXIT_FAILURE); //Using exit() for now, till a better solution has been thought of.
    }

    lockSimulator = new LockSimulator();

    cout << "Simulator is starting..." << endl;
}

int StateMachine::init() {
    if(communicate->sendTestRequest()){
        return IDLE; //Test frame successful, start normal operations.
    } else {
    	cout << "Sending test frame failed." << endl;
        return ERROR; //Test frame failed, go to error.
    }

    cout << "Simulator is initialized." << endl;
}

int StateMachine::error() {
	cout << "Error state reached. In 10 seconds, initialization will be redone, press Ctrl+C to exit." << endl;
	sleep(10);
	return INIT;
}

void StateMachine::runStateMachine() {
    ResponseAnswer answer;

    while(true){
        switch(state){
            case IDLE:
                if(lockSimulator->detectEntry()){
                    state = COMMUNICATE;
                } else {
                    state = IDLE;
                }
                break;
            case COMMUNICATE:
                try {
                    answer = communicate->sendRequest(lockSimulator->getUserIdentifier(), lockSimulator->getPincode());
                    state = PROCESS_OUTPUT;
                } catch (HanException& ex) {
                    state = ERROR;
                    cout << "Communication with server failed." << endl;
                    Logger::warning("Communication with server failed: " + ex.getMessage());
                }
                break;
            case PROCESS_OUTPUT:
                lockSimulator->setOutput(answer);
                state = IDLE;
                break;
            case ERROR:
                state = error();
                break;
            case INIT:
                state = init();
                break;
            default:
                cerr << "No valid state selected" << endl << "Exiting program" << endl;
                exit(0);
        }
    }
}

bool StateMachine::interruptHandler() {
	switch(state) {
		case IDLE:
		case ERROR:
			cout << "Simulator will exit." << endl;
			exit(EXIT_SUCCESS);
			return true;
		default:
			cout << "Interruption signal received but ignored." << endl;
			return false;
	}
}
