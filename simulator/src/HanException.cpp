/* 
 * File:   HanException.cpp
 * Author: nathanael
 * 
 * Created on May 9, 2012, 10:20 AM
 */

#include "HanException.h"

HanException::HanException() {
}

HanException::~HanException() {
}

string HanException::getMessage() {
    exception = "Error";
    return exception;
}
