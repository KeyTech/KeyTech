#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

using namespace std;

/**
 * Logger utility class for logging messages. All messages will standard be logged to the standard error stream.
 */
class Logger {
public:
	/**
	 * Log a message with log level DEBUG.
	 * @param message The message. '%syserr' will be replaced by the last system error.
	 */
	static void debug(string message);

	/**
	 * Log a message with log level INFO.
	 * @param message The message. '%syserr' will be replaced by the last system error.
	 */
	static void info(string message);

	/**
	 * Log a message with log level WARNING.
	 * @param message The message. '%syserr' will be replaced by the last system error.
	 */
	static void warning(string message);

	/**
	 * Log a message with log level ERROR.
	 * @param message The message. '%syserr' will be replaced by the last system error.
	 */
	static void error(string message);

private:
	static void log(string level, string message);
};

#endif /* LOGGER_H_ */
