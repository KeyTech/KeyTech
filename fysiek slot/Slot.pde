//#include <IO.h>
//#include <Communication.h>
#include <CardReader.h>
#include <Frames.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

//States
#define INIT 0
#define IDLE 1
#define COMMUNICATE 2
#define PROCESS_OUTPUT 3
#define ERROR 4

//General defines
#define LOCK_NUMBER 1
#define LCD A0 //LCD pin
#define LOCK_PIN A1 //Lock relay pin
#define OPEN_LOCK true
#define CLOSE_LOCK false
#define ID_LENGTH 6
#define PIN_LENGTH 4

//Keypad defines
#define ROWS 4 //four rows
#define COLS 4 //four columns

//LCD defines
#define CLEAR_SCREEN 12 //LCD clear screen instruction

//Request defines:
#define REQ_TESTFRAME B00000001
#define REQ_INCORRECT_CHECKSUM B00000010
#define REQ_LOCK_OPEN B00000100
#define REQ_LOCK_CLOSED 0
//Response defines:
#define RES_PERMISSION_GRANTED B00000001
#define RES_INCORRECT_ID B00000010
#define RES_NO_ACCESS B00000100
#define RES_USER_BLOCKED B00010000
#define RES_BAD_CHECKSUM B00100000
#define RES_TEST_RESPONSE B01000000

//Com defines:
#define DELAY 100 //Wait 1000 milliseconds.
#define BAUD_RATE 9600
#define LOCAL_PORT 8888
#define TRIES 3
#define SERVICE_PORT 8000
#define ATTEMPT_FAILED 0

//Error flags:
#define DETECT_ENTRY_FAILED 0
#define SEND_REQUEST_FAILED 1
#define PROCESS_OUTPUT_FAILED 2
#define INIT_FAILED 3

//Init delay
#define INIT_DELAY 3000
#define READ_DELAY 2000

//Keypad variables:
char keys[ROWS][COLS] = {
  {'1','2','3', 'a'},
  {'4','5','6', 'b'},
  {'7','8','9', 'c'},
  {'*','0','#', 'd'}
};
byte rowPins[ROWS] = {0, 1, 8, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

//Global variables.
int next_state;
int flags;
uint8_t *request;
uint16_t lockID;
uint32_t userID;
uint16_t pincode;
volatile bool lockState;
bool booting;
IPAddress serviceIP(192,168,1,5);

////main functions:
//bool initLock();
////Com functions
//bool initCom();
//int sendRequest(const uint32_t *userID, const uint16_t *pincode, bool lockstatus);
//bool sendTestRequest();
//bool sendData();
//bool receiveData();
//bool sendAndReceiveData();
////IO functions
//bool initIO();
//bool detectEntry();
//bool setOutput(int flags);
//void setLockState(bool state);
//bool getLockState();
//bool askUserID();
//bool askPin();
//uint32_t getUserIdentifier();
//uint16_t getPinCode();
//void playEntrySound();

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
SoftwareSerial mySerial = SoftwareSerial(255, A0); //RX, TX. RX is not used so it's assigned a bogus pin.
//IO io;
//Communication com;
Frames Frame;
EthernetClass Eth;
EthernetUDP UDP;
CardReader CR;

void setup()
{
	booting = true;
	//Serial.begin(BAUD_RATE);
	mySerial.begin(BAUD_RATE);
	pinMode(A0, OUTPUT);
	digitalWrite(A0, HIGH);
	delay(100);
	//Serial.print("Starting program");
	attachInterrupt(0, emergencyExit, RISING);
	next_state = INIT;
}

void loop()
{
switch(next_state) {
		case IDLE:
			if(detectEntry()) {
				next_state = COMMUNICATE;
			} else {
				flags = DETECT_ENTRY_FAILED;
				next_state = ERROR;
			}
			break;
		case COMMUNICATE:
			if((flags = sendRequest(getUserIdentifier(), getPinCode(), getLockState())) != ATTEMPT_FAILED) {
				next_state = PROCESS_OUTPUT;
			} else {
				flags = SEND_REQUEST_FAILED;
				next_state = ERROR;
			}
			break;
		case PROCESS_OUTPUT:
			if(setOutput(flags)){
				delay(READ_DELAY);
				next_state = IDLE;
			} else {
				flags = PROCESS_OUTPUT_FAILED;
				next_state = ERROR;
			}
			break;
		case ERROR:
			processError(flags);
			delay(READ_DELAY);
			next_state = INIT;
			break;
		case INIT:
			if(initLock()){
				delay(INIT_DELAY);
				next_state = IDLE;
			} else {
				flags = INIT_FAILED;
				next_state = ERROR;
			}
			break;
		default:
			break;
	}
}

bool initLock() {
	lockID = LOCK_NUMBER;
	
	mySerial.write(CLEAR_SCREEN); delay(5);
	if(!initIO()) {
		writeLCD("initIO failed");
		delay(READ_DELAY);
		return false;
	}
	if(initCom()) {
		writeLCD("initCom success");
		return true;
	} else {
		writeLCD("initCom failed");
		delay(READ_DELAY);
		return false;
	}
}

void emergencyExit() {
	setLockState(OPEN_LOCK);
}

void processError(int flags) {
	writeLCD("Error: ");
	mySerial.print(flags);
	switch(flags) {
	case DETECT_ENTRY_FAILED:
		mySerial.print(" (detectEntry)");
		next_state = INIT;
		break;
	case SEND_REQUEST_FAILED:
		mySerial.print(" (Request)");
		next_state = INIT;
		break;
	case PROCESS_OUTPUT_FAILED:
		mySerial.print(" (setOutput)");
		next_state = INIT;
		break;
	case INIT_FAILED:
		mySerial.print(" (init)");
		next_state = INIT;
		break;
	default:
		mySerial.print(" Unknown error");
		next_state = INIT;
		break;
	}
}

void showIP() {
	writeLCD("My IP address: ");
			for (byte thisByte = 0; thisByte < 4; thisByte++) {
				// print the value of each byte of the IP address:
				mySerial.print(Ethernet.localIP()[thisByte], DEC);
				mySerial.print("."); 
			}
			delay(READ_DELAY);
}
IPAddress IP(0,0,0,0);

//Communication related functions
bool initCom() {
	// start the Ethernet connection:
	byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
	if(booting) {
		writeLCD("DHCP: starting");
		if (Eth.begin(mac) == 0) { //Arduino really doesn't like it when you rerun this code without a hard reset. Why?
			writeLCD("DHCP: failed");
			return false;
		} else {
			UDP.begin(SERVICE_PORT);
			booting = false;
			showIP();
			writeLCD("DHCP: success   Sending testreq");
			if(sendTestRequest()){
				return true;
			} else {
				return false;
			}
		}
	} else {
		showIP();
		if(sendTestRequest()){
			return true;
		} else {
			return false;
		}
	}
}

int sendRequest(const uint32_t *userID, const uint16_t *pincode, bool lockstatus) {
	uint8_t flags = 0;
	uint8_t status = REQ_LOCK_CLOSED;
	if(lockstatus) status = REQ_LOCK_OPEN;

	Frame.createRequest(&lockID, userID, pincode, &flags, &status);
	//Unlike sendTestRequest this request only happens once. The network should be fine once we get to this stage.
	if(sendAndReceiveData()) {
		if((flags = Frame.getResponseFlags()) != RES_TEST_RESPONSE) {
			return flags; //Received response was indeed a proper answer.
		} else {
			 return ATTEMPT_FAILED; //Returned answer is an unexpected test frame answer.
		}
	} else {
		 return ATTEMPT_FAILED;//Sending or receiving data failed.
	}
}

bool sendTestRequest() {
	uint8_t test = REQ_TESTFRAME;
	uint32_t zero = 0;
	Frame.createRequest(&lockID, &zero, (uint16_t*) &zero, &test, (uint8_t*) &zero);
	for(int i=0; i<TRIES; i++) { //Try a couple of times to perform a test - response sequence.
		writeLCD("Try: ");
		mySerial.print(i);
		if(sendAndReceiveData()) {
			if(Frame.getResponseFlags() == RES_TEST_RESPONSE) {
				return true; //Received response was indeed a testframe response.
			} else {
				continue; //Returned answer was not a testframe response.
			}
		} else {
			continue; //Sending or receiving data failed.
		}
	}
	return false;
}

bool sendAndReceiveData() {
	int rec_bytes;
	int counter = 0;
	for(int i = 0; i < TRIES; i++) {
		if(sendData()) {
			do {
				rec_bytes = UDP.parsePacket();
				counter++;
				//mySerial.print(rec_bytes, DEC);
				delay(10);
			} while (rec_bytes == 0 && counter < 100); //< Frame.getFrameSize() ); //Wait until the complete Frame datagram has come in. Waits maximum 100*10 ms. (1s)
			if(rec_bytes > 0) {
				if(receiveData()) {
					return true;
				} else {
					delay(DELAY); //Wait a while before trying again.
					continue;
				}
			} else {
				return false;
			}			
		} else {
			delay(DELAY); //Wait a while before trying again.
			continue;
		}
	}
	return false; //Sending and receiving failed.
}

/*If I understand the UCP header+cpp files correctly it's also possible to use a host name instead of an IP address. This
host name is converted to an IP via a DNS lookup. This should be tested for later use as it would allow us to use a completely
dynamic IP system in which only the server needs to get registered at a DNS service.*/
bool sendData() {
	if(UDP.beginPacket(serviceIP, SERVICE_PORT)) { //1 if building packet was succesful.
		UDP.write(Frame.getRequestFrame(), Frame.getFrameSize());
		if(UDP.endPacket()) { //1 is sending has been succesful.
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool receiveData() {
	UDP.read((char*)Frame.getReponseFrame(), Frame.getFrameSize());
	if(Frame.checkResFrame()){
		if(Frame.getResponseFlags() != RES_BAD_CHECKSUM && Frame.getResponseLockID() == lockID && Frame.getResponseUserID() == userID) {
		//if(Frame.getResponseFlags() != RES_BAD_CHECKSUM) {	
			return true;
		} else {
			return false; //Checksum, lockID or userID in response from service failed. Resend the frame.
		}
	} else {
//Checksum incorrect, got to ask again. Question: should the incorrect checksum flag be set or should the whole request just be redone?
		return false;
	}
}

//IO related functions:
#define IO   A2    // Input/Output Pin
#define CD   A3     // Card Detect Pin
#define RST  A4    // Reset Pin
#define CLK  A5    // Clock Pin

bool initIO() {
	//Keypad pin setup (keypad uses digital 0-8 pins). Pin 2 is INT0! (interrupt 0);
	//writeLCD("InitIO started");
	for (int i = 0; i < 8; i++)  {
		if(i == 2) continue;
		pinMode(i, INPUT);
		digitalWrite(i, HIGH);
	}

	//Lock relay pin. Currently closes the lock on start up.
	pinMode(LOCK_PIN, OUTPUT);
	digitalWrite(LOCK_PIN, LOW);
	setLockState(CLOSE_LOCK);

	//CardReader:
	if (CR.IsCardDetected()) {
		writeLCD("Please remove card.");
		delay(READ_DELAY);
		return false;
	}
	return true; //Currently nothing here can fail. Perhaps later on with the card reader?
}

bool detectEntry() {
	do {
		writeLCD("Enter your ID:  ");
	}
	while(!askUserID()); // keep looping until a correct length ID was entered
	//do {
	//	writeLCD("Please insert your ID card.");
	//} while(!cardReaderEntry());
	do{
		writeLCD("Enter your pin: ");
	} while(!askPin()); // keep looping until a correct length password was entered
	writeLCD("Identification done");
	//delay(3000);
	return true;
}

//The mySerials showing the entered data is for debug purposes only.
bool cardReaderEntry() {
	if (CR.IsCardDetected()) {
		userID = CR.Read_Main();
		writeLCD("User ID: ");
		mySerial.print(userID);
		delay(READ_DELAY);
		return true;
	} else {
		delay(READ_DELAY);
		return false;
	}
}

//Replaced by the card reader.
bool askUserID() {
	char digits[ID_LENGTH]; // temp array to hold the entered digits
  for (int i = 0; i < ID_LENGTH; i++)			{ // get the password
	  digits[i] = keypad.waitForKey(); 
	  mySerial.print(digits[i]);	

	  if(digits[i] == '*') { //the user pressed reset
		  //mySerial.write(CLEAR_SCREEN); delay(5); // clear the LCD
		  //mySerial.print("Enter your ID:  ");
		  //i = -1; 	       }  
		  return false;
	  }
	  if(isalpha(digits[i]) || digits[i] == '#')  { // a letter was entered
		  writeLCD("You can only enter numbers");
		  delay(READ_DELAY);
		  return false;		      }
  }

  delay(500);
  userID = atol(digits); // convert the temp array to the ID number (uint32_t)
  writeLCD("Your ID: ");
  mySerial.println(userID);
  delay(READ_DELAY);
  return true;
}

//The mySerials showing the entered data is for debug purposes only.
bool askPin() {
  char digits[PIN_LENGTH]; // temp array to hold the entered digits
  for (int i = 0; i < PIN_LENGTH; i++) { // get the password
	  digits[i] = keypad.waitForKey();  
	  mySerial.print(digits[i]);

	  if(digits[i] == '*') { //the user pressed reset
		  //i = -1;		   }
		  return false;
	  }

	  if(isalpha(digits[i]) || digits[i] == '#')  { // a letter was entered
		  writeLCD("You can only enter numbers.");
		  delay(READ_DELAY);
		  return false;		      }
  }

  pincode = atoi(digits); // convert the char array to the pin (uint16_t)

  delay(500);
  writeLCD("Your pincode: ");
  mySerial.println(pincode);
  delay(READ_DELAY);

  return true;
}

bool setOutput(int flags) {
	switch(flags) {
		case RES_PERMISSION_GRANTED:
			if(getLockState()){ //Open lock == true
				setLockState(CLOSE_LOCK);
			} else {
				setLockState(OPEN_LOCK);
			}
			writeLCD("Request granted");
			return true;
		case RES_INCORRECT_ID:
			writeLCD("Incorrect ID");
			return true;
		case RES_NO_ACCESS:
			writeLCD("Access denied at this time.");
			return true;
		case RES_USER_BLOCKED:
			writeLCD("You have been blocked.");
			return true;
		default:
			return false;
	}
}

/*If this isn't stable enough, add a pull-down resistor to ground. Alternatively, you can use the internal pull-up resistor.
This would flip the working of the LED/relay: currently the LED is off when locked and on when open.
Use the following code for reverse behaviour:
-Changes to init:
pinMode(LOCK_PIN, INPUT);
digitalWrite(LOCK_PIN, HIGH);
pinMode(LOCK_PIN, OUTPUT);

-And then change the digitalWrites below to LOW/HIGH instead of HIGH/LOW.
*/
void setLockState(bool state) {
	lockState = state;
	if(lockState) { //if lock is open, drive the relay/LED.
		digitalWrite(LOCK_PIN, HIGH);
	} else { //if closed, do nothing.
		digitalWrite(LOCK_PIN, LOW);
	}
}

bool getLockState() {
	return lockState;
}

uint32_t* getUserIdentifier() {
	return &userID;
}

uint16_t* getPinCode() {
	return &pincode;
}

//void playEntrySound() {
//	//DEC 214 set note length to full note (2 seconds)
//	//DEC 216 select 4th scale (440 - 831 Hz)
//	//DEC 223 play a C. (Sound with a frequency of 523 Hz)
//	mySerial.write(214);
//	mySerial.write(216);
//	mySerial.write(223);
//}

void writeLCD(const char* text) {
	mySerial.write(CLEAR_SCREEN);
	delay(5);
	mySerial.print(text);
}