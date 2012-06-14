#include <iostream>
#include <ctime>
#include <errno.h>
#include <string.h>

#include "Logger.h"

using namespace std;

void Logger::debug(string message) {
	Logger::log("DEBUG", message);
}

void Logger::info(string message) {
	Logger::log("INFO ", message);
}

void Logger::warning(string message) {
	Logger::log("WARNING", message);
}

void Logger::error(string message) {
	Logger::log("ERROR", message);
}

void Logger::log(string level, string message) {
	time_t timestamp = time(NULL);
	struct tm *currentTime = localtime(&timestamp);
	char time[20];

	if(message.find("%syserr") != string::npos) {
		message.replace(message.find("%syserr"), strlen("%syserr"), strerror(errno));
	}

	strftime(time, 20, "%d-%m-%Y %H:%M:%S", currentTime);

	cerr << level << " [" << time << "]: " << message << endl;
}
