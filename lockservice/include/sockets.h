/* 
 * File:   sockets.h
 * Author: tristan braak
 *
 * Created on May 3, 2012, 10:06 PM
 */

#ifndef SOCKETS_H
#define	SOCKETS_H

#include <iostream>
#include "errorHandling.h"
#include <string.h>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include <errno.h>           // For errno
typedef void raw_type;       // Raw data

using namespace std;

/** 
 * Sockets class
 */ 
class Sockets {
public:
    
  /**
   * Close and deallocate this socket
   */
  ~Sockets();
  
  Sockets();
       
  /**
   * Set a specified local port and local address
   * @param localaddress server
   * @param localPort server
   */
  void setLocalAddressAndPort(const string &localaddress, unsigned short &localPort) throw(ErrorHandling);
  
  virtual void sendTo(const void *buffer, int bufferLen, const string &foreignAddress, unsigned short foreignPort) throw(ErrorHandling);
  
  virtual int recvFrom(void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort) throw(ErrorHandling);
  
private:
    
protected:      
  int socketDesc; // Socket Descriptor
       
  /**
   * Basic Socket Constructor 
   * @param type of datagram
   * @param protocol type
   */
  Sockets(int type, int protocol) throw(ErrorHandling);       
};

/**
 * UDP sockets extens sockets
 */ 
class UDPSocket : public Sockets {
public:
   
  /**
   * Constructor UDP socket
   * @param localaddress to use
   * @param localPort to use
   */
  UDPSocket(const string &localaddress, unsigned short &localPort) throw(ErrorHandling);
       
   /**
   * Close and deallocate this UDPsocket
   */
  ~UDPSocket();
   
  /**
   * Send the given UDP datagram
   * @param buffer to be send
   * @param bufferLen number of bytes to send
   * @param foreignAddress to send
   * @param foreignPort to send
   */
  void sendTo(const void *buffer, int bufferLen, const string &foreignAddress, unsigned short foreignPort) throw(ErrorHandling);
  
  /**
   * Block until the socket is receiving bytes.
   * @param buffer received data
   * @param bufferLen maximum bytes to receive
   * @param sourceAddress datagram source
   * @param sourcePort port source
   * @return the number of bytes read
   */
  int recvFrom(void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort) throw(ErrorHandling);
        
};

#endif	/* SOCKETS_H */

