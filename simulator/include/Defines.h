#ifndef DEFINES_H
#define	DEFINES_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>

using namespace std;

/*! \brief Exit statuses:
 * 
 */
#define INCORRECT_NO_ARGUMENTS 2
#define ERR_INET_PTON 3

/*! \brief Other:
 * 
 */
#define SUCCESS 1
//#define FAIL 0
#define OPEN true
#define CLOSED false
#define ID_LENGTH 6
#define PIN_LENGTH 4

typedef enum {
    PERMISSION_GRANTED, INCORRECT_ID, NO_ACCESS, USER_BLOCKED,
} ResponseAnswer;

#endif	/* DEFINES_H */
