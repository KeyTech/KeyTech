#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include <stdint.h>
#include <string>
#include "NetworkException.h"

using namespace std;

/**
 * UDP client. This class can be used to setup a UDP datagram with some server.
 */
class UdpClient {
public:
	UdpClient(string serverAddress, uint16_t port) throw (NetworkException);

	void send(void *data, int dataLength) throw (NetworkException);

	void receive(void *buffer, int bufferLength) throw (NetworkException);

	void setTimeout(int seconds, int microseconds);
private:
	struct timeval timeout;
    sockaddr_in serverAddress;
    int socketDescriptor;
};

#endif /* UDPCLIENT_H_ */
