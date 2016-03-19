#include "GraphicsHandler.h"



GraphicsHandler::GraphicsHandler(int w, int h, const char* title)
{
}

Window* GraphicsHandler::getWindow()
{
	return window;
}

void GraphicsHandler::drawBegin()
{
	window->clear();
}

void GraphicsHandler::drawEnd()
{
	window->display();
}

void GraphicsHandler::close()
{
	window->close();
}



GraphicsHandler::~GraphicsHandler()
{
}
