#include "Logs/Log.h"


Log::Log(std::string _message): message(_message)
{

}

std::string Log::content()
{
	return message;
}