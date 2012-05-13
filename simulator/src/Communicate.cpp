#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/select.h>
#include <string.h>
#include <errno.h>

#include "Logger.h"
#include "Communicate.h"
#include "Defines.h"

Communicate::Communicate(string serverAddress, uint16_t port, uint16_t lockIdentifier) throw(HanException):
	lockIdentifier(lockIdentifier) {

	try {
		client = new UdpClient(serverAddress, port);
		client->setTimeout(TIMEOUT, 0);
	} catch(NetworkException& ex) {
		throw new HanException(ex.getMessage());
	}
};

ResponseAnswer Communicate::sendRequest(uint32_t userIdentifier, uint16_t pincode) throw(HanException) {
    HanRequest request;
    HanResponse response;
    
    request.setKeyIdentifier(lockIdentifier);
    request.setCode(pincode);
    request.setUserIdentifier(userIdentifier);
    
    sendAndReceiveData(request, response);

    if(response.getKeyIdentifier() != lockIdentifier || response.getUserIdentifier() != userIdentifier) {
        throw HanException("Received incorrect response from server.");
    }

    return response.getAnswer();
}

bool Communicate::sendTestRequest() {
    HanRequest request;
    HanResponse response;

    request.setTestFrame(true);

    try {
    	sendAndReceiveData(request, response);
    } catch(HanException& ex) {
    	return false;
    }

    if(!response.isTestFrameAnswer()) {
    	Logger::warning("Received answer from server after sending test frame, but answer was not a test frame answer.");
    	return false;
    }

    return true;
}

void Communicate::sendAndReceiveData(HanRequest request, HanResponse response) throw(HanException) {
    for (int i = 0; ; i++) {
    	try {
    	    sendData(request);
    	    receiveData(response);
    	} catch(HanException& ex) {
    		if(i >= RETRIES) {
    			throw ex;
    		} else {
    			Logger::warning("Sending or receiving failed. [ " + ex.getMessage() + " ]");
    		}
    	}
	}
}

void Communicate::sendData(HanRequest request) throw (HanException) {
	try {
		client->send(request.getFrame(), request.getFrameSize());
	} catch(NetworkException& ex) {
		throw HanException(ex.getMessage());
    }
}

void Communicate::receiveData(HanResponse response) throw (HanException) {
	try {
		char buffer[response.getFrameSize()];
		client->receive(buffer, response.getFrameSize());
		response.setFrame(buffer);
	} catch(NetworkException& ex) {
		throw HanException(ex.getMessage());
	}
}
