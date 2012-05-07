/* 
 * File:   han.h
 * Author: root
 *
 * Created on April 23, 2012, 10:44 AM
 */

#ifndef HAN_H
#define	HAN_H

// Request flags
#define SIT_NORM 0b00000000
#define TEST_FRAME 0b00000001
#define ERR_LOCK_CHECKSUM 0b00000010

// Response flags
#define PERMISSION_GRANTED 0b00000001
#define ERR_ID_INCORRECT 0b00000010
#define ERR_UNAUTHORISED 0b00000100
#define ERR_BLOCKED 0b00001000
#define ERR_SERVER_CHECKSUM 0b00010000
#define TEST_FRAME_ANSWER 0b00100000

// Reqeust struct
typedef struct 
{
   short int slotnummer;
   int IDnummer;
   short int pincode;
   unsigned char flags;
   unsigned char critData;
   short int checksum;
} request_arch;

// Response struct
typedef struct 
{
   short int slotnummer;
   int IDnummer;
   unsigned char flags;
   unsigned char critData[3];
   short int checksum;
} response_arch;

#endif	/* HAN_H */

