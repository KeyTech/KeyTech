#include "Exception.h"

Exception::Exception(char* message): message(message) {}

char *Exception::getMessage() {
    return message;
}