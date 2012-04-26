#ifndef HANEXCEPTION_H
#define	HANEXCEPTION_H

#include "Exception.h"

class HanException : public Exception {
public:
    HanException(char *message): Exception(message) {}
};

#endif	/* HANEXCEPTION_H */