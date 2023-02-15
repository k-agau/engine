#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "Logs/Log.h"

class Logger
{
private:
	std::ostream& console;
public:
	Logger();
	void emit(Log& log);
};

#endif // LOGGER_H