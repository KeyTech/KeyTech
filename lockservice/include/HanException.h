#ifndef HANEXCEPTION_H
#define	HANEXCEPTION_H

#include <string>

using namespace std;

class HanException {
public:
	HanException(string message);
    string getMessage();

private:
    string message;
};

#endif