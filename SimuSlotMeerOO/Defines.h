/* 
 * File:   Defines.h
 * Author: nathanael
 *
 * Created on April 23, 2012, 1:23 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

/*! \brief General includes:
 * 
 */
#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>

using namespace std;

/*! \brief SimuLock client related defines:
 * 
 */
typedef struct Response_Packet {
    short locknr;
    short checksum;
    int id;
    unsigned char flags;
    unsigned char data[3];      
} response_packet;

typedef struct {
        short locknr;
        short checksum;
        int id;
        short pincode;
        unsigned char flags;
        unsigned char data;      
} request_packet;

/*! \brief Exit statuses:
 * 
 */
#define INCORRECT_NO_ARGUMENTS 2
#define ERR_INET_PTON 3

/*! \brief Other:
 * 
 */
#define SUCCESS 1
#define FAIL 0
#define OPEN true
#define CLOSED false
#define ID_LENGTH 6
#define PIN_LENGTH 4

#endif	/* DEFINES_H */

