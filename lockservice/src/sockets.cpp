/* 
 * File:   sockets.cpp
 * Author: tristan braak
 *
 * Created on May 3, 2012, 10:06 PM
 */
 
#include "sockets.h"

using namespace std;

/**
 * Fill sockaddr structures
 */
static void fillAddr(const string &address, unsigned short &port, sockaddr_in &addr) {
    
  const char *buf;
  buf = address.c_str();                    // We dont want to break the inner string structure
  
  memset(&addr, 0, sizeof(addr));           // Zero out structure
  addr.sin_family = AF_INET;                // Internet 4 address
  inet_pton(AF_INET, buf, &addr.sin_addr);  // Assign address in network byte order 
  addr.sin_port = htons(port);              // Assign port in network byte order
}

/**
 * Socket Code
 */
Sockets::Sockets(){
    
}

Sockets::Sockets(int type, int protocol) throw(ErrorHandling){
    
    // Make a new socket
  if ((socketDesc = socket(PF_INET, type, protocol)) < 0) {
    throw ErrorHandling("Socket creation failed (socket())", true);
  }
}

Sockets::~Sockets(){
  socketDesc = -1;
}

void Sockets::setLocalAddressAndPort(const string &localaddress, unsigned short &localPort) throw(ErrorHandling){  
    
  sockaddr_in serverAddr;
  fillAddr(localaddress, localPort, serverAddr);

  if (bind(socketDesc, (sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0) {
    throw ErrorHandling("Set of local port failed (bind())", true);
  }
}



void Sockets::sendTo(const void *buffer, int bufferLen, const string &foreignAddress, unsigned short foreignPort) throw(ErrorHandling){
    
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Write out the whole buffer as a single message.
  if (sendto(socketDesc, (raw_type *) buffer, bufferLen, 0,(sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen) {
    throw ErrorHandling("Send failed (sendto())", true);
  }
}

int Sockets::recvFrom(void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort) throw(ErrorHandling) {
    
  sockaddr_in clntAddr;
  socklen_t addrLen = sizeof(clntAddr);
  int rtn;
  
  if ((rtn = recvfrom(socketDesc, (raw_type *) buffer, bufferLen, 0, (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0) {
    throw ErrorHandling("Receive failed (recvfrom())", true);
  }
  
  sourceAddress = inet_ntoa(clntAddr.sin_addr);
  sourcePort = ntohs(clntAddr.sin_port);

  return rtn;
}


/**
 * UDPSocket Code
 */
UDPSocket::UDPSocket(const string &localaddress, unsigned short &localPort) throw(ErrorHandling)
: Sockets(SOCK_DGRAM, IPPROTO_UDP) {
    
  setLocalAddressAndPort(localaddress, localPort);
}

UDPSocket::~UDPSocket(){
}

void UDPSocket::sendTo(const void *buffer, int bufferLen, const string &foreignAddress, unsigned short foreignPort) throw(ErrorHandling){
    
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Write out the whole buffer as a single message.
  if (sendto(socketDesc, (raw_type *) buffer, bufferLen, 0,(sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen) {
    throw ErrorHandling("Send failed (sendto())", true);
  }
}

int UDPSocket::recvFrom(void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort) throw(ErrorHandling) {
    
  sockaddr_in clntAddr;
  socklen_t addrLen = sizeof(clntAddr);
  int rtn;
  
  if ((rtn = recvfrom(socketDesc, (raw_type *) buffer, bufferLen, 0, (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0) {
    throw ErrorHandling("Receive failed (recvfrom())", true);
  }
  
  sourceAddress = inet_ntoa(clntAddr.sin_addr);
  sourcePort = ntohs(clntAddr.sin_port);

  return rtn;
}