#include "GraphicsHandler.h"



GraphicsHandler::GraphicsHandler(int w, int h, const char* title)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Default, settings);
	glEnable(GL_TEXTURE_2D);
}

void GraphicsHandler::setTitle(const char* title)
{
	window->setTitle(title);
}

void GraphicsHandler::setFPS(int fps)
{
	window->setFramerateLimit(fps);
}

sf::RenderWindow* GraphicsHandler::getWindow()
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

void GraphicsHandler::drawSprite(Sprite* sprite, int x, int y)
{

}


GraphicsHandler::~GraphicsHandler()
{
	delete window;
}
