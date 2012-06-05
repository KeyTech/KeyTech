/* 
IO library for the network lock program.
Copyright (c) 2012 Nathanael Zitter
*/

// include core Wiring API
#include <Arduino.h>

// include this library's description file
#include "IO.h"

// include description files for other libraries used (if any)
#include <Keypad.h>
#include <SoftwareSerial.h>

IO::IO()
{
	initIO();
}

IO::~IO() {}

bool IO::initIO() {
	char keys[ROWS][COLS] = {
	  {'1','2','3', 'a'},
	  {'4','5','6', 'b'},
	  {'7','8','9', 'c'},
	  {'*','0','#', 'd'}
	};
	byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
	byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad	

	keypad = new Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
	mySerial = new SoftwareSerial(255, LCD); //RX, TX. RX is not used so it's assigned a bogus pin.

	//Keypad pin setup (keypad uses digital 0-7 pins);
	for (int i = 0; i < 8; i++)  {
		pinMode(i, INPUT);
		digitalWrite(i, HIGH);
	}

	//Lock relay pin.
	pinMode(LOCK_PIN, OUTPUT);
	digitalWrite(LOCK_PIN, LOW);
	setLockState(OPEN_LOCK);

	//Emergency exit pin:
	pinMode(EMERGENCY_EXIT_PIN, INPUT);

	return true;
}

bool IO::detectEntry() {
	while(!askUserID()); // keep looping until a valid ID was entered
	while(!askPin()); // keep looping until a valid password was entered
	mySerial->write(CLEAR_SCREEN);
	mySerial->println("Identification  done");
	return true;
}

//The mySerials showing the entered data is for debug purposes only.
bool IO::askUserID() {
  char digits[ID_LENGTH]; // temp array to hold the entered digits

  mySerial->write(CLEAR_SCREEN); // clear the LCD
  mySerial->print("Enter your ID:  ");
  
  for (int i = 0; i < ID_LENGTH; i++)			{ // get the password
	  digits[i] = keypad->waitForKey(); 
	  mySerial->print(digits[i]);	

	  if(digits[i] == '*') { //the user pressed reset
		  //mySerial->write(CLEAR_SCREEN); // clear the LCD
		  //mySerial->print("Enter your ID:  ");
		  //i = -1; 	       }  
		  return false;
	  }
	  if(isalpha(digits[i]) || digits[i] == '#')  { // a letter was entered
		  mySerial->write(CLEAR_SCREEN); // clear the LCD
		  mySerial->write("You can only enter numbers");
		  delay(3000);
		  return false;		      }
  }

  delay(500);
  mySerial->write(CLEAR_SCREEN); // clear the LCD

  userID = atol(digits); // convert the temp array to the ID number (uint32_t)

  mySerial->print("Your id: ");
  mySerial->println(userID);
  delay(2000);
  
  return true;
}

//The mySerials showing the entered data is for debug purposes only.
bool IO::askPin() {
  char digits[PIN_LENGTH]; // temp array to hold the entered digits

  mySerial->write(CLEAR_SCREEN); // clear the LCD
  mySerial->print("Enter your pin: ");
  
  for (int i = 0; i < PIN_LENGTH; i++) { // get the password
	  digits[i] = keypad->waitForKey();  
	  mySerial->print(digits[i]);

	  if(digits[i] == '*') { //the user pressed reset
		  //i = -1;		   }
		  return false;
	  }

	  if(isalpha(digits[i]) || digits[i] == '#')  { // a letter was entered
		  mySerial->write(CLEAR_SCREEN); // clear the LCD
		  mySerial->write("You can only enter numbers");
		  delay(3000);
		  return false;		      }
  }

  pincode = atoi(digits); // convert the char array to the pin (uint16_t)

  delay(500);
  mySerial->write(CLEAR_SCREEN); // clear the LCD

  mySerial->print("Your pincode:   ");
  mySerial->println(pincode);
  delay(2000);

  return true;
}

bool IO::setOutput(int flags) {
	switch(flags) {
		case RES_PERMISSION_GRANTED:
			if(getLockState()){ //Open lock == true
				setLockState(CLOSE_LOCK);
			} else {
				setLockState(OPEN_LOCK);
			}
			playEntrySound();
			return true;
		case RES_INCORRECT_ID:
			mySerial->write(CLEAR_SCREEN);
			mySerial->write("Incorrect ID");
			return true;
		case RES_NO_ACCESS:
			mySerial->write(CLEAR_SCREEN);
			mySerial->write("Access denied at this time.");
			return true;
		case RES_USER_BLOCKED:
			mySerial->write(CLEAR_SCREEN);
			mySerial->write("You have been blocked.");
			return true;
		default:
			return false;
	}
}

/*If this isn't stable enough, add a pull-down resistor to ground. Alternatively, you can use the internal pull-up resistor.
This would flip the working of the LED/relay: by default the LED would be on for locked and off for open. Use the following code then:
Changes to init:
pinMode(LOCK_PIN, INPUT);
digitalWrite(LOCK_PIN, HIGH);
pinMode(LOCK_PIN, OUTPUT);

And then change the digitalWrites below to LOW/HIGH instead of HIGH/LOW.
*/
void IO::setLockState(bool state) {
	lockState = state;
	if(lockState) { //if lock is open, drive the relay/LED.
		digitalWrite(LOCK_PIN, HIGH);
	} else { //if closed, do nothing.
		digitalWrite(LOCK_PIN, LOW);
	}
}

bool IO::getLockState() {
	return lockState;
}

uint32_t IO::getUserIdentifier() {
	return userID;
}

uint16_t IO::getPinCode() {
	return pincode;
}

void IO::playEntrySound() {
	//DEC 214 set note length to full note (2 seconds)
	//DEC 216 select 4th scale (440 - 831 Hz)
	//DEC 223 play a C. (Sound with a frequency of 523 Hz)
	mySerial->write(214);
	mySerial->write(216);
	mySerial->write(223);
}

void IO::emergencyExitButton() {
	int reading = digitalRead(EMERGENCY_EXIT_PIN);
	if (reading != lastButtonState) {
		lastDebounceTime = millis();
	} 
	if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
		if(!getLockState()){ //If lock's closed...
			setLockState(OPEN_LOCK);
		} //else: do nothing, door's already open.
	}
	lastButtonState = reading;
}