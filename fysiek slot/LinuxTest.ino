#include <SPI.h>
#include <Ethernet.h>


//Includes:



//Defines

typedef enum {

	PERMISSION_GRANTED, INCORRECT_ID, NO_ACCESS, USER_BLOCKED,

} ResponseAnswer;



#define INIT 0

#define IDLE 1

#define COMMUNICATE 2

#define PROCESS_OUTPUT 3

#define ERROR 4



#define OPEN_LOCK true

#define CLOSE_LOCK false

#define ID_LENGTH 6

#define PIN_LENGTH 4



//Class headers:

class HanFrame {

public:

	HanFrame();

	~HanFrame();



	/**

	 * @return Retrieve the frame, ready to be sent.

	 */

	void *getFrame();



	/**

	 *

	 * @return returns the size of the frame.

	 */

	int getFrameSize();



	/**

	 * Sets the frame.

	 * @param frame Pointer to the frame. Should have a size equal to the framesize.

	 * @see getFrameSize()

	 */

	void setFrame(void *frame);



protected:

	enum frameDefinition {

		CHECKSUM = 10,

		FRAME_SIZE = 12,

	};



	uint8_t frame[FRAME_SIZE];



	uint16_t calculateChecksum();

};



class HanRequest : public HanFrame {

public:

	HanRequest();

	~HanRequest();

	

	/**

	 * Set the identifier of the key sending this request frame.

	 * @param keyIdentifier Key identifier.

	 */

	void setKeyIdentifier(uint16_t keyIdentifier);

	

	uint16_t getKeyIdentifier();



	/**

	 * Set the user identifier.

	 * @param userIdentifier Identifier identifing the user.

	 */

	void setUserIdentifier(uint32_t userIdentifier);

	

	uint32_t getUserIdentifier();



	/**

	 * Set the code used by the user to identifier him/herself.

	 * @param code The code.

	 */

	void setCode(uint16_t code);

	

	uint16_t getCode();



	/**

	 * Set to TRUE if this is a testFrame, FALSE (default) otherwise.

	 * @param testFrame Is this a test frame?

	 */

	void setTestFrame(bool testFrame);

	

	/**

	 * @return TRUE if this is a testframe, FALSE otherwise.

	 */

	bool isTestFrame();

	

	/**

	 * Set the lock status. TRUE for locked, FALSE for not locked.

	 * @param lockStatus

	 */

	void setLockStatus(bool lockStatus);

	

	/**

	 * @return TRUE if lock was locked while sending this request, FALSE otherwise.

	 */

	bool isLocked();



private:

	enum responseDefinition {

		KEY_IDENTIFIER = 0,

		USER_IDENTIFIER = 2,

		PINCODE = 6,

		FLAGS = 8,

	};



	enum flags {

		TEST_FRAME = B00000001,

		INCORRECT_CHECKSUM = B00000010,

		LOCKED = B00000100

	};

};



class HanResponse : public HanFrame{



public:

	HanResponse();

	~HanResponse();

	

	/**

	 * @return The identifier of the key sending this frame.

	 */

	uint16_t getKeyIdentifier();

	

	/**

	 * Set the key identifier.

	 * @param keyIdentifier Key identifier.

	 */

	void setKeyIdentifier(uint16_t keyIdentifier);



	/**

	 * @return The user identifier.

	 */

	uint32_t getUserIdentifier();

	

	/**

	 * Set the user identifier.

	 * @param userIdentifier User identifier.

	 */

	void setUserIdentifier(uint32_t userIdentifier);

	

	

	/**

	 * Is this frame an answer to a test frame?

	 * @return TRUE if answer to test frame, FALSE otherwise.

	 */

	bool isTestFrameAnswer();



	/**

	 * Is this an answer to a test frame?

	 * @param testFrameAnswer TRUE if an answer to a test frame, FALSE otherwise.

	 */

	void setTestFrameAnswer(bool testFrameAnswer);



	/**

	 * Get the answer this frame contains.

	 * @return The answer.

	 * @see ResponseAnswer

	 */

	ResponseAnswer getAnswer();



	/**

	 * Set the answer this frame contains.

	 * @param answer The answer.

	 * @see ResponseAnswer

	 */

	void setAnswer(ResponseAnswer answer);



	/**

	 * @deprecated

	 */

	bool checkChecksum();



private:

	enum responseDefinition {

		KEY_IDENTIFIER = 0,

		USER_IDENTIFIER = 2,

		FLAGS = 6,

	};

	

	enum flags {

		F_PERMISSION_GRANTED = B00000001,

		F_INCORRECT_ID = B00000010,

		F_NO_ACCESS = B00000100,

		F_USER_BLOCKED = B00010000,

		F_BAD_CHECKSUM = B00100000,

		F_TEST_RESPONSE = B01000000

	};

};



class UdpClient {

public:

	UdpClient(String saddr, uint16_t port); //Constructor

	~UdpClient();

	

	void send(void *data, int dataLength);

	void receive(void *buffer, int bufferlength);

	void setTimeout(int seconds, int microseconds);

	

private:

	// struct timeval timeout;

	// sockaddr_in saddr;

	int socket_descriptor;

};





class Communicate {

public:

	Communicate(); //Constructor

	~Communicate();

	

	ResponseAnswer sendRequest(uint32_t userID, uint16_t pincode);

	bool sendTestRequest();

	

private:

	void sendData(HanRequest *request);

	void receiveData(HanResponse *response);

	void sendAndReceiveData(HanRequest *request, HanResponse *response);

	

	UdpClient *client;

	

	//sockaddr_in saddr;

	uint16_t lockID;

	int socket_descriptor;

};



class IO {

public:

	IO(); //Constructor

	~IO();

	

	bool detectEntry();

	bool setOutput(ResponseAnswer flags);

	void setLockState(bool state);

	bool getLockState();

	uint32_t getUserID();

	uint16_t getPin();

	

private:

	uint32_t userID;

	uint16_t pincode;

	bool lockState;

};


//Class functions:

IO::IO() {
  
}

IO::~IO() {
  
}

Communicate::Communicate() {}

Communicate::~Communicate() {}

//Global vars

IO io;

Communicate coms;

int next_state;



//Initial setup

void setup() {

	next_state = IDLE;

}



//Main loop, which is pretty much equivalent to a state machine.

void loop() {

	switch(next_state) {

		case IDLE:

			break;

		case COMMUNICATE:

			break;

		case PROCESS_OUTPUT:

			break;

		case ERROR:

			break;

		case INIT:

			break;

		default:

			break;

	}

}


