#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

#include "Communicate.h"
#include "Defines.h"

Communicate::Communicate(string serverAddress, uint16_t port, uint16_t lockIdentifier) throw(HanException):
	lockIdentifier(lockIdentifier) {

    bzero(&this->serverAddress, sizeof(struct sockaddr_in));
	this->serverAddress.sin_family = AF_INET;

	if(inet_pton(AF_INET, serverAddress.c_str(), &(this->serverAddress.sin_addr)) != 1) {
		throw HanException("Could not convert server address. Was it malformed?");
	}

	this->serverAddress.sin_port = htons(port);

	socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
};

ResponseAnswer Communicate::sendRequest(uint32_t userIdentifier, uint16_t pincode) throw(HanException) {
    HanRequest request;
    HanResponse response;
    char buffer[response.getFrameSize()];
    socklen_t addressLength = sizeof(struct sockaddr_in);
    
    request.setKeyIdentifier(lockIdentifier);
    request.setCode(pincode);
    request.setUserIdentifier(userIdentifier);
    
    if(sendto(socketDescriptor, request.getFrame(), request.getFrameSize(), 0, (const struct sockaddr*) &serverAddress, addressLength) != request.getFrameSize()) {
        throw HanException("Could not sent to server.");
    }

    if((recvfrom(socketDescriptor, buffer, sizeof(buffer), 0, (struct sockaddr*) &serverAddress, &addressLength)) != sizeof(buffer)) {
        throw HanException("Did not receive correct data from the server.");
    }

    response.setFrame(buffer);
    if(response.getKeyIdentifier() != lockIdentifier || response.getUserIdentifier() != userIdentifier) {
        throw HanException("Received incorrect response from server.");
    }

    return response.getAnswer();
}

bool Communicate::sendTestRequest() {
	return true;
}
