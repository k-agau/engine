#include "Logs/Logger.h"

Logger::Logger(): console(std::cout)
{
}

void Logger::emit(Log& log)
{
	console << log.content() << std::endl;
}