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
