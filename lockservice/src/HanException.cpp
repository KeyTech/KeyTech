#include "HanException.h"

HanException::HanException(string message) :
	message(message) {}

string HanException::getMessage() {
    return message;
}