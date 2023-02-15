#ifndef LOG_H
#define LOG_H

// TODO: Make this abstract and have base log classes?

#include <string>

class Log
{
private:
	std::string message;
public:
	Log(std::string _message);
	std::string content();
};

#endif // LOG_H