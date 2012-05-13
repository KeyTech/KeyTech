#include "NetworkException.h"

NetworkException::NetworkException(string message) :
	message(message) {}

string NetworkException::getMessage() {
    return message;
}
