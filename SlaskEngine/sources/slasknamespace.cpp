#include "slasknamespace.h"

GraphicsHandler* slask::graphics()
{
	return GraphicsHandler::instance();
}

InputHandler* slask::input()
{
	return InputHandler::instance();
}

AudioHandler* slask::audio()
{
	return AudioHandler::instance();
}

LogHandler* slask::log()
{
	return LogHandler::instance();
}

SteamHandler* slask::steam()
{
	return SteamHandler::instance();
}

File slask::file()
{
	return File::File();
}
