/* 
 * File:   HanException.h
 * Author: nathanael
 *
 * Created on May 9, 2012, 10:20 AM
 */

#ifndef HANEXCEPTION_H
#define	HANEXCEPTION_H

#include "Defines.h"

class HanException {
public:
    HanException();
    ~HanException();
    
    string getMessage();
    
private:
    string exception;
};

#endif	/* HANEXCEPTION_H */

