// THIS SOFTWARE IS PROVIDED TO YOU "AS IS," AND WE MAKE NO EXPRESS OR IMPLIED WARRANTIES WHATSOEVER
// WITH RESPECT TO ITS FUNCTIONALITY, OPERABILITY, OR USE, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR INFRINGEMENT. WE EXPRESSLY
// DISCLAIM ANY LIABILITY WHATSOEVER FOR ANY DIRECT, INDIRECT, CONSEQUENTIAL, INCIDENTAL OR SPECIAL
// DAMAGES, INCLUDING, WITHOUT LIMITATION, LOST REVENUES, LOST PROFITS, LOSSES RESULTING FROM BUSINESS
// INTERRUPTION OR LOSS OF DATA, REGARDLESS OF THE FORM OF ACTION OR LEGAL THEORY UNDER WHICH THE
// LIABILITY MAY BE ASSERTED, EVEN IF ADVISED OF THE POSSIBILITY OR LIKELIHOOD OF SUCH DAMAGES.

// Use Card 32321

// This Sample Application Performs the following (All Output goes to the //Serial Monitor):
//
// 1 - Resets Card
// 2 - Authenticates Password (FF FF FF).
//     Note: Being that I locked my first card ... and then found out even the PBasic 2.5 and Propeller Demos would automatically lock after 3 card inserts
//           I have taken pains to make sure that it shouldn't happen again ...
//           but if you need that type of security ...
//           you may want to look at the compare function and make some changes.
//           But for testing ... locking up the card (so you can't write values) shouldn't be possible with this code (but no guarantees).
// 3 - Writes characters 0 through 255 to memory location 0 through 255 (although location 0 will stay at A2)
// 4 - Displays a memory dump
// 5 - Clears all memory locations (sets all locations to 0 although again, location 0 will stay at A2)
// 6 - Displays another memory dump.
//
// Components required:
//
// An Arduino or compatible should work ...
//    I tested with an Arduino UNO SMD and an Arduino Mega 2560 R3 ... both worked.
// A Parallax Smart Card Reader.
// A IS23SC4442 (32321) Smart Card.
//
#include <Arduino.h>

#include "CardReader.h"

CardReader::CardReader()
{
	CardDetected = 0;   // Last Card Detect Event
	delayamt = 50;      // Default Delay Amount (in Microseconds)
	Input(CD);
}

bool CardReader::IsCardDetected()
{
  return Get(CD);
}


void CardReader::Reset()
{
  //Serial.println("Reset.");
  Output(CLK);
  Input(IO);
  Output(RST);
  Set_Low(RST);
  Set_Low(CLK);
  Set_High(RST);
  delayMicroseconds(delayamt); // A little extra wait time for this
  Set_High(CLK);
  Set_Low(CLK);
  delayMicroseconds(delayamt); // A little extra wait time for this
  Set_Low(RST);
  //long address = 0;
  for (int index = 0; index < 4; index++)
  {
	Receive_Byte();
  }
}

uint8_t CardReader::Authenticate()
{
  //Serial.println("Authenticating...");

  uint8_t errCounter = Compare();
  return errCounter;
 // switch (errCounter)
 // {
	//case 0x00:  // Hopefully we'll NEVER see this ... because once it's locked it can't be unlocked as far as I know
	//  //Serial.println(" Card is locked.");
	//  break;
	//case 0x01:
	//  //Serial.println(" Invalid PSC, one try remaining.");
	//  break;
	//case 0x03:
	//  //Serial.println(" Invalid PSC, two tries remaining.");
	//  break;
	//case 0x07:
	//  //Serial.println(" PSC verified, you may now write data to the card.");
	//  break;
	//default:
	//  //Serial.println(" Unabled to Authenticate.");
	//  break;
 // }

  //Serial.println(" Done.");
}

uint8_t CardReader::Compare()
{
  uint8_t Data = 0x03;  // Just make sure we never lock the Card

  uint8_t Password1 = 0xFF;  // 1st byte of PSC
  uint8_t Password2 = 0xFF;  // 2nd byte of PSC
  uint8_t Password3 = 0xFF;  // 3rd byte of PSC

  uint8_t errCounter = Read_Security();

  errCounter = errCounter & 0x07;

  switch (errCounter)
  {
	case 0x07:
	  Data = 0x03;
	  break;
	case 0x03:
	  Data = 0x03;  // was 0x01 ... only one less and we'll lock the card
	  break;
	case 0x01:
	  Data = 0x03;  // was 0x00 ... which will lock the Card
	  break;
	case 0x00:
	  Data = 0x03;
	  break;
  }

  Send_Command(UpdateSecurity, 0x00, Data);

  Send_Command(CompareData, 0x01, Password1);

  Send_Command(CompareData, 0x02, Password2);

  Send_Command(CompareData, 0x03, Password3);

  Send_Command(UpdateSecurity, 0x00, 0x07);   // Reset Counter to it's highest value (so we don't ever lock the Card)

  return errCounter;
}

uint32_t CardReader::Read_Main()
{
  //Serial.println("Read Main...");
  //uint8_t bytes[INT_LENGTH];
  uint32_t password = 0;
  uint8_t *ptr = (uint8_t*) &password;

  Send_Command(ReadMain, 0x00, 0x00);

  for (int index = 1; index <= INT_LENGTH; index++)
  {
	*ptr = Receive_Byte();
	ptr++;
  }

  //int number = (ID_LENGTH-1);

  //for (int i = 0; i < ID_LENGTH; i++)
  //{
	 // password += (bytes[i] * power(10, number--));
  //}

  //Serial.println(password);
  return password;
}

void CardReader::Update_Main(uint8_t Address, uint8_t Data)
{
  Send_Command(UpdateMain, Address, Data);
}

uint8_t CardReader::Read_Security()
{
  //Serial.println(" Read Security...");

  Send_Command(ReadSecurity, 0x00, 0x00);
  uint8_t errCounter = Receive_Byte();

 /* Send_Command(ReadSecurity, 0x01, 0x00);
  uint8_t PSW1 = Receive_Byte();

  Send_Command(ReadSecurity, 0x02, 0x00);
  uint8_t PSW2 = Receive_Byte();

  Send_Command(ReadSecurity, 0x03, 0x00);
  uint8_t PSW3 = Receive_Byte();*/

  //Serial.print("  errCounter = ");
  //Serial.print((uint8_t)errCounter, HEX);
  //Serial.print(", PSW1 = ");
  //Serial.print((uint8_t)PSW1, HEX);
  //Serial.print(", PSW2 = ");
  //Serial.print((uint8_t)PSW2, HEX);
  //Serial.print(", PSW3 = ");
  //Serial.print((uint8_t)PSW3, HEX);
  //Serial.println("");
  //Serial.println("  Done.");

  return errCounter;
}

void CardReader::Send_Command(uint8_t Command, uint8_t Address, uint8_t Data)
{
  Output(CLK);
  Set_High(CLK);
  Output(IO);
  Set_Low(IO);
  _SendToCard(Command);
  _SendToCard(Address);
  _SendToCard(Data);
  Set_Low(CLK);
  Set_Low(IO);
  Set_High(CLK);
  Set_High(IO);

  if (Command == UpdateMain || Command == UpdateProtection || Command == CompareData || Command == UpdateSecurity)
	Processing();
}

void CardReader::_SendToCard(uint8_t cmd)
{
	uint8_t command = cmd;
	bool temp = 0;

	for (int i = 0; i < 8; i++)
	{
	  temp = command & 0x01;
	  command = command >> 1;
	  Set_Low(CLK);
	  if (temp != 0)
		Set_High(IO);
	  else
	    Set_Low(IO);
	   Set_High(CLK);
	}
}

uint8_t CardReader::Receive_Byte()
{
  return _ReceiveFromCard();
}

uint8_t CardReader::_ReceiveFromCard()
{
  uint8_t data = 0;
  bool bit = 0;

  Output(CLK);
  Input(IO);
  Set_High(CLK);

  for (int i = 0; i < 8; i++)
  {
	  data = data >> 1;
	  Set_Low(CLK);
	  Set_High(CLK);
	  bit = Get(IO);
	  if (bit)
	  {
		data += 0x80;
	  }
  }

  return data;
}

void CardReader::Processing()
{
  Input(IO);
  Set_Low(CLK);

  while (Get(IO) == 0)
  {
	Set_High(CLK);
	Set_Low(CLK);
  }
}

void CardReader::Set_Low(int Pin)
{
  digitalWrite(Pin, LOW);
  delayMicroseconds(delayamt);
}

void CardReader::Set_High(int Pin)
{
  digitalWrite(Pin, HIGH);
  delayMicroseconds(delayamt);
}

bool CardReader::Get(int Pin)
{
  return digitalRead(Pin);
}

void CardReader::Input(int Pin)
{
  pinMode(Pin, INPUT);
}

void CardReader::Output(int Pin)
{
  pinMode(Pin, OUTPUT);
}

uint32_t CardReader::power(uint32_t a, uint32_t b)
{
	 uint32_t c=a;
	 for (int n=b; n> 0; n--) c*=a;
	 return c;
}

void CardReader::writeID(uint32_t ID) {
	uint8_t *pID = (uint8_t*) &ID;
	for(int i = 1; i<=INT_LENGTH; i++) {
		Update_Main(((uint8_t) i), pID[i]); 
	}
}