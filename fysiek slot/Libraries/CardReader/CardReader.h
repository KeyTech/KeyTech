/*
  CardReader.h - Library for reading/writing to the smart card.
  Created by Hanna Hermsen on 31-5-2012
*/

#include <Arduino.h>

#ifndef CardReader_h
#define CardReader_h


////defines for the mega1280
//#define IO   41    // Input/Output Pin
//#define CLK  43    // Clock Pin
//
//#define RST  47    // Reset Pin
//#define CD   45     // Card Detect Pin

//defines for a Dueminanove
#define IO   A2    // Input/Output Pin
#define CD   A3     // Card Detect Pin
#define RST  A4    // Reset Pin
#define CLK  A5    // Clock Pin


#define ReadMain           0x30  // Read main memory
#define ReadProtection     0x34  // Read protection bit
#define ReadSecurity       0x31  // Read PSC
#define UpdateMain         0x38  // Update main memory
#define UpdateSecurity     0x39  // Update PSC
#define UpdateProtection   0x3C  // Update Protection bits
#define CompareData        0x33  // Compare Verification Data

#define ID_LENGTH 6
#define INT_LENGTH 4

// includes
#include "Arduino.h"
#include <stdio.h>
#include <stdlib.h>

class CardReader
{
	public:

	CardReader();

	/*Read the data on the card
	*/
	uint32_t Read_Main();

	/*Writes a 32 bit long ID number to the first 4 bytes of the card.
	* @param ID number to be written.
	*/
	void writeID(uint32_t ID);

	/*Write data to the card
	*@param Address is the memory location to write to
	*@param Data is the data to write
	*/
	void Update_Main(uint8_t Address, uint8_t Data);

	/*Checks if a card is inserted
	*@return 0 means no card inserted, 1 means a card is inserted
	*/
	bool IsCardDetected();

	/*Resets the data on the card
	*/
	void Reset();

	/*Checks the password on the card
	*/
	uint8_t Authenticate();

	private:

	/*Reads the password on the card
	*/
	uint8_t Compare();

	/*Handles the card protection
	@return The error number
	*/
	uint8_t Read_Security();

	/*Sends a command to the card
	*@param Command is the command to send to the card
	*@param Address is the address to send the command to
	*@param Data is the data to write
	*/
	void Send_Command(uint8_t Command, uint8_t Address, uint8_t Data);

	/*Sends data to the card
	*@param cmd is the data/command to write to the card
	*/
	void _SendToCard(uint8_t cmd);

	/*Gets data from card
	*@return the received byte
	*/
	uint8_t _ReceiveFromCard();

	/*Returns the received byte from the card
	*@return The data that was read by _ReceiveFromCard()
	*/
	uint8_t Receive_Byte();

	/*Sets CLK from HIGH to LOW
	*/
	void Processing();

	/*Sets a pin to LOW
	*@param The pin to set LOW
	*/
	void Set_Low(int Pin);

	/*Sets a pin to HIGH
	*@param The pin to set HIGH
	*/
	void Set_High(int Pin);

	/*Reads from a pin
	*@param The pin to read from
	*@return 0(LOW) or 1(HIGH)
	*/
	bool Get(int Pin);

		/*Sets a pin as input
	*@param The pin to set as input
	*/
	void Input(int Pin);

	/*Sets a pin as output
	*@param The pin to set as output
	*/
	void Output(int Pin);

	/*Raises a number to a defined power
	*@param a is the number
	*@param b is the power
	*@return the result
	*/
	uint32_t power(uint32_t a, uint32_t b);

	bool CardDetected;   // 0, Last Card Detect Event
	int delayamt;      // 50, Default Delay Amount (in Microseconds)
};

#endif
