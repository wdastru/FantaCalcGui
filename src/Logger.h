/*
 * Logger.h
 *
 *  Created on: 19/nov/2011
 *      Author: WAleViolaeIvan
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "singletonQtLogger.h"

class Logger: public singletonQtLogger {
public:
	Logger();
	~Logger();
};

#endif /* LOGGER_H_ */
