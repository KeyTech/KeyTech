#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>

#include "Logger.h"
#include "NetworkException.h"
#include "UdpClient.h"

UdpClient::UdpClient(string serverAddress, uint16_t port) throw(NetworkException) {
    bzero(&this->serverAddress, sizeof(struct sockaddr_in));
	this->serverAddress.sin_family = AF_INET;

	if(inet_pton(AF_INET, serverAddress.c_str(), &(this->serverAddress.sin_addr)) != 1) {
		throw NetworkException("Could not convert server address. Was it malformed?");
	}

	this->serverAddress.sin_port = htons(port);

	if((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		Logger::warning("socket() system call failed: %syserr");
		throw NetworkException("Failed to create socket.");
	}
}

void UdpClient::setTimeout(int seconds, int microseconds) {
	this->timeout.tv_sec = seconds;
	this->timeout.tv_usec = microseconds;
}

void UdpClient::receive(void *buffer, int bufferLength) throw(NetworkException) {
    unsigned int addressLength = sizeof(serverAddress);
    fd_set descriptors;

    FD_ZERO(&descriptors);
    FD_SET(socketDescriptor, &descriptors);

    if(select(socketDescriptor + 1, &descriptors, NULL, NULL, &timeout) == -1) {
    	Logger::warning("select() system call failed: %syserr");
    	throw NetworkException("Receiving data from server failed.");
    }
    if(FD_ISSET(socketDescriptor, &descriptors)) {
    	if((recvfrom(socketDescriptor, buffer, bufferLength, 0, (struct sockaddr*) &serverAddress, &addressLength)) != bufferLength) {
    	        throw NetworkException("Did not receive correct data from the server.");
    	}
    } else {
    	throw NetworkException("Did not receive any data from the server.");
    }
}

void UdpClient::send(void *data, int dataLength) throw(NetworkException) {
    if(sendto(socketDescriptor, data, dataLength, 0, (const struct sockaddr*) &serverAddress, sizeof(serverAddress)) != dataLength) {
        throw NetworkException("Could not sent to server.");
    }
}
