/* 
 * File:   LockService.h
 * Author: torisuta
 *
 * Created on May 14, 2012, 11:59 AM
 */

#ifndef LOCKSERVICE_H
#define	LOCKSERVICE_H

#include "sockets.h"
#include "dbconnector.h"
#include "errorHandling.h"
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include <errno.h>           // For errno
#include <stdio.h>

using namespace std;

const int MAXBUFSIZE = 1024;

class LockService {
public:
    LockService() throw(ErrorHandling);
    ~LockService();
private:

};

#endif	/* LOCKSERVICE_H */

