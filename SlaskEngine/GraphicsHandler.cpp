#include "GraphicsHandler.h"



GraphicsHandler::GraphicsHandler(int w, int h, const char* title)
{
	ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	window = new RenderWindow(VideoMode(w, h), title, Style::Default, settings);

}

void GraphicsHandler::setTitle(const char* title)
{
	window->setTitle(title);
}

void GraphicsHandler::setFPS(int fps)
{
	window->setFramerateLimit(fps);
}

RenderWindow* GraphicsHandler::getWindow()
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
	delete window;
}
