/* 
Frames library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

#ifndef IO_H
#define IO_H

#include <Arduino.h>

#define LCD A0 //LCD pin
#define LOCK_PIN A1 //Lock relay pin
#define EMERGENCY_EXIT_PIN 8
#define DEBOUNCE_DELAY 50
#define OPEN_LOCK true
#define CLOSE_LOCK false
#define ID_LENGTH 6
#define PIN_LENGTH 4
#define CLEAR_SCREEN 12
#define ROWS 4 //four rows
#define COLS 4 //four columns

#define RES_PERMISSION_GRANTED B00000001
#define RES_INCORRECT_ID B00000010
#define RES_NO_ACCESS B00000100
#define RES_USER_BLOCKED B00010000

class Keypad;
class SoftwareSerial;

class IO
{
public:
	IO();
	~IO();

	/**Performs the necessary inits on the external devices.
	*/
	bool initIO();
	/** Handles all the work needed to process a potential entry.
	*/
	bool detectEntry();
	/** Sets the output according to the flags given back by Communication.
	* @param flags, the flag given by Com.
	*/
	bool setOutput(int flags);
	/** Sets the new physical state of the lock.
	* @param state, the state the lock should get into.
	*/
	void setLockState(bool state);
	/**
	* @return lockstate, returns the current physical state of the lock.
	*/
	bool getLockState();
	/** Asks the user to enter their ID number.
	*/
	bool askUserID();
	/** Asks the user for their pin code.
	*/
	bool askPin();
	/**
	* @return userID, returns the entered userID.
	*/
	uint32_t getUserIdentifier();
	/**
	* @return pincode, returns the entered pin code.
	*/
	uint16_t getPinCode();
	/**
	*/
	void emergencyExitButton();

private:
	uint32_t userID;
	uint16_t pincode;
	bool lockState;
	int lastButtonState;
	int lastDebounceTime;

	/**Plays a two second long entry sound.
	*/
	void playEntrySound();

	Keypad *keypad;
	SoftwareSerial *mySerial;
};

#endif //IO_H