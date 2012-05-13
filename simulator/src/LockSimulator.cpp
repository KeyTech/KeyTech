#include <limits>
#include <string>

#include "LockSimulator.h"
#include "Logger.h"

using namespace std;

LockSimulator::LockSimulator(istream *is) :
	stream(is) {
}

LockSimulator::LockSimulator()	{
	stream = &cin;
}

bool LockSimulator::detectEntry() {
	userIdentifier = 0;
	pincode = 0;

	string userIdentifierInput, pincodeInput;

	try {
		cout << "Please enter your 6 digit student ID." << endl;
		getline(*stream, userIdentifierInput);
		userIdentifier = atoi(userIdentifierInput.c_str());

		if (userIdentifierInput.length() != 6 || userIdentifier < 0) {
			throw "User identifier should be 6 digits long.";
		}

		cout << "Please enter your 4 digit pin code." << endl;
		getline(*stream, pincodeInput);

		pincode = atoi(pincodeInput.c_str());

		if (pincodeInput.length() != 4) {
			throw "Pin code should be 4 digits long.";
		}

		Logger::info("Input read: userIdentifier: " + userIdentifierInput + ", pin code: " + pincodeInput);
		return true;
	} catch (const char *error) {
		cout << error << endl;
		Logger::warning("Reading input failed. Incorrect input.");
		return false;
	}
}

bool LockSimulator::setOutput(ResponseAnswer flags) {
	switch (flags) {
		case PERMISSION_GRANTED:
			cout << "Permission to change lock state granted." << endl;
			if (getLockState() == OPEN) {
				setLockState(CLOSED);
				cout << "Door is now locked." << endl;
			} else {
				setLockState(OPEN);
				cout << "Door is now unlocked." << endl;
			}
			return true;
		case INCORRECT_ID:
			cout << "Could not identificate user." << endl;
			return true;
		case NO_ACCESS:
			cout << "Not authorized for this lock at this time." << endl;
			return true;
		case USER_BLOCKED:
			cout << "User is blocked for some reasen by server. (To many authentication attempts?)" << endl;
			return true;
	}
}

void LockSimulator::setLockState(bool state) {
	lockState = state;
}

bool LockSimulator::getLockState() {
	return lockState;
}

uint32_t LockSimulator::getUserIdentifier() {
	return userIdentifier;
}

uint16_t LockSimulator::getPincode() {
	return pincode;
}
