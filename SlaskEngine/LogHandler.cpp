#include "LogHandler.h"


LogHandler* LogHandler::instance()
{
	static LogHandler loghandler;
	return &loghandler;
}

void LogHandler::writeLog(const char *logger,const char *str,int type)
{
	//TODO
}

void LogHandler::log(const char *str)
{
	writeLog(0, str, Log);
}

void LogHandler::error(const char *str)
{
	writeLog(0, str, Error);
}

void LogHandler::error(const char* logger,const char *str)
{
	writeLog(logger, str, Error);
}

void LogHandler::log(const char *logger,const char *str)
{
	writeLog(logger, str, Log);
}

void LogHandler::notify(const char *str)
{
	writeLog(0, str, Notify);
}

void LogHandler::init()
{
}


LogHandler::~LogHandler()
{
}
