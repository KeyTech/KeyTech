/* 
 * File:   SlotIO.cpp
 * Author: nathanael
 * 
 * Created on April 23, 2012, 1:15 PM
 */

#include "LockSimulator.h"
#include <limits>
#include <string>

using namespace std;

bool LockSimulator::detectEntry() {
	studentID = 0;
	pin = 0;

	string input;

	cout << "Please enter your 6 digit student ID." << endl;
	getline(cin, input);
	studentID = atoi(input.c_str());

	cout << "Please enter your 4 digit pin code." << endl;
	getline(cin, input);
	pin = atoi(input.c_str());

	//test to see if I get it right:
	cout << "studentID: " << studentID << endl << "Pin: " << pin << endl;

	if (studentID > 0 && pin > 0) {
		cout << "Entry succesful" << endl;
		return true;
	} else {
		cout << "Invalid entry. Please try again" << endl;
		return false;
	}
}

int LockSimulator::setOutput(uint8_t flags) {
	switch (flags) {
		case PERMISSION_GRANTED:
			cout << "Permission to change door state granted." << endl;
			if (GetDoorState()) { //OPEN == true.
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
			cout << "Too many attempts done. You have been banned for x time."
					<< endl;
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

void LockSimulator::SetDoorState(bool state) {
	door_state = state;
}

bool LockSimulator::GetDoorState() {
	return door_state;
}

uint32_t LockSimulator::getStudentId() {
	return studentID;
}

uint16_t LockSimulator::getPin() {
	return pin;
}
