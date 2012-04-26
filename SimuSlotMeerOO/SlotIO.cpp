/* 
 * File:   SlotIO.cpp
 * Author: nathanael
 * 
 * Created on April 23, 2012, 1:15 PM
 */

#include "SlotIO.h"

SlotIO::SlotIO() {
}

SlotIO::SlotIO(const SlotIO& orig) {
}

SlotIO::~SlotIO() {
    cout << "SlotIO has been destroyed." << endl;
}

bool SlotIO::detectEntry() {
    studentID = 0;
    pin = 0;
    char str[13]; //length = 6 chars studentID, 1 space, 4 pin, 1 \n, 1\0 = 13 bytes long
    memset(str, '\0', sizeof(str));
    cout << "Please enter your 6 digit student ID." << endl;
    fgets(str, (ID_LENGTH + 2), stdin); //+2 for carriage return and terminating zero.
    if(strcspn(str, "\n") != ID_LENGTH ) { //+1 for the extra carriage return character.
        cout << "Invalid studentID" << endl;
        FLUSH_STDIN(str);
        return false;
    }
    FLUSH_STDIN(str);
    studentID = atoi(str);
    cout << "Please enter your 4 digit pin code." << endl;
    fgets(str, (PIN_LENGTH + 2), stdin);
    if(strcspn(str, "\n") != PIN_LENGTH ) {
        cout << "Invalid pin" << endl;
        FLUSH_STDIN(str);
        return false;
    }
    FLUSH_STDIN(str);
    pin = atoi(str);
    //test to see if I get it right:
    cout << "studentID: " << studentID << endl << "Pin: " << pin << endl;
    
    if(studentID > 0 && pin > 0) {
        cout << "Entry succesful" << endl;
        return true;
    } else {
        cout << "Invalid entry. Please try again" << endl;
        return false;
    }
}

int SlotIO::setOutput(uint8_t flags) {
    switch(flags){
        case PERMISSION_GRANTED:
            cout << "Permission to change door state granted." << endl;
            if(GetDoorState()) { //OPEN == true.
                SetDoorState(CLOSED);
                cout << "Door is now locked." << endl;
            } else {
                SetDoorState(OPEN);
                cout << "Door is now unlocked." << endl;
            }
            return true;
        case ERR_ID_INCORRECT:
            cout << "ID incorrect." << endl;
            return true;
        case ERR_UNAUTHORISED:
            cout << "Unauthorized access at this time." << endl;
            return true;
        case ERR_BLOCKED:
            cout << "Too many attempts done. You have been banned for x time." << endl;
            return true;
        case ERR_SERVER_CHECKSUM:
            cout << "Server message checksum failed." << endl;
            return false;
        case TEST_FRAME_ANSWER:
            cout << "The test frame was sent successfully ." << endl;
            return true;
        default:
            cout << "No known response flag." << endl;
            return false;
    }
}

void SlotIO::SetDoorState(bool state) {
    door_state = state;
}

bool SlotIO::GetDoorState() {
    return door_state;
}

uint32_t SlotIO::getStudentID() {
    return studentID;
}

uint16_t SlotIO::getPin() {
    return pin;
}