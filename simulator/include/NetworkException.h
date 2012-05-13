#ifndef NETWORKEXCEPTION_H_
#define NETWORKEXCEPTION_H_

#include <string>

using namespace std;

class NetworkException {
public:
	NetworkException(string message);
    string getMessage();

private:
    string message;
};

#endif /* NETWORKEXCEPTION_H_ */
