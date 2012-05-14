/* 
 * File:   errorHandling.h
 * Author: torisuta
 *
 * Created on May 10, 2012, 10:44 AM
 */

#ifndef ERRORHANDLING_H
#define	ERRORHANDLING_H

#include <string>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

/**
 *   Signals a problem with the execution of a socket call.
 */
class ErrorHandling : public exception {
public:
  /**
   *   Construct a SocketException with a explanatory message.
   *   @param message explanatory message
   *   @param incSysMsg true if system message (from strerror(errno))
   *   should be postfixed to the user provided message
   */
  ErrorHandling(const string &message, bool inclSysMsg) throw();

  /**
   *   Provided just to guarantee that no exceptions are thrown.
   */
  ~ErrorHandling() throw();

  /**
   *   Get the exception message
   *   @return exception message
   */
  const char *what() const throw();

private:
  string userMessage;  // Exception message
};

#endif	/* ERRORHANDLING_H */

