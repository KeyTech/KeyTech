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
    cout << "State Machine started." << endl;
        //Com settings:
    bzero(&saddr, sizeof(struct sockaddr_in));
    if(argc == 4) {
        saddr.sin_family = AF_INET;
        if(inet_pton(AF_INET, argv[1], &saddr.sin_addr) < 0 ) {
            perror("inet_pton error in init.");
            exit(ERR_INET_PTON);
        }
        saddr.sin_port = htons(atoi(argv[2]));
        if( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <0) {
            perror("Socket creation error");
        }
    } else {
        cout << "Incorrect number of parameters. Enter server IP, port number and lock no." << endl;
        exit(INCORRECT_NO_ARGUMENTS);
    }
        //lockID:
    lockID = atoi(argv[3]);
}

bool StateMachine::init() {
    //SlotIO:
	lockSimulator.SetDoorState(OPEN);

    return true;
}

void StateMachine::runStateMachine() {
    uint8_t flags = 0;
    int messages_sent = 0;
    while(true){
        //cout << "Next_state: " << next_state << endl;
        switch(next_state){
            case IDLE:
                cout << "Test state IDLE" << endl;
                if(lockSimulator.detectEntry()){
                    next_state = SEND;
                } else {
                    next_state = IDLE;
                }
                break;
            case SEND:
                cout << "Test state SEND" << endl;
                if((messages_sent < 3) && (communicate.sendRequest(&saddr, sockfd, lockID, lockSimulator.getStudentId(), lockSimulator.getPin() )) ) {
                    next_state = RECEIVE;
                    cout << "Messages sent: " << messages_sent << endl;
                    messages_sent += 1;
                } else if(messages_sent >= 3) {
                    cout << "Max attempts reached." << endl;
                    next_state = IDLE;
                    messages_sent = 0;
                } else {
                    next_state = SEND;
                    cout << "Messages sent: " << messages_sent << endl;
                    messages_sent += 1;
                }
                break;
            case RECEIVE:
                cout << "Test state RECEIVE" << endl;
                if((flags = communicate.receiveResponse(&saddr, sockfd, lockID)) > 0 ) {
                    next_state = PROCESS_OUTPUT;
                    messages_sent = 0;
                } else {
                    next_state = SEND;
                }
                break;
            case PROCESS_OUTPUT:
                cout << "Test state PROCESS_OUTPUT" << endl;
                if(lockSimulator.setOutput(flags) ) {
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

