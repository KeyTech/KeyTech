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

typedef enum {
    PERMISSION_GRANTED, INCORRECT_ID, NO_ACCESS, USER_BLOCKED,
} ResponseAnswer;

#endif	/* DEFINES_H */