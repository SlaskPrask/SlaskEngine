#include "LogHandler.h"


LogHandler* LogHandler::instance()
{
	static LogHandler loghandler;
	return &loghandler;
}

void LogHandler::init()
{
}


LogHandler::~LogHandler()
{
}
