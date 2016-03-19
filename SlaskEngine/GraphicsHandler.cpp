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
	setTitle(title);
	setVSync(true);
	setFPS(60);
	glEnable(GL_TEXTURE_2D);
	setSize(w, h);
}

void GraphicsHandler::setTitle(const char* title)
{
	label = title;
	window->setTitle(title);
}

void GraphicsHandler::setFPS(int fps)
{
	framespersecond = fps;
	window->setFramerateLimit(fps);
}

void GraphicsHandler::setVSync(bool enabled)
{
	vsync = enabled;
	window->setVerticalSyncEnabled(enabled);
}

void GraphicsHandler::setSize(int w, int h)
{
	width = w;
	height = h;
}

int GraphicsHandler::getWidth()
{
	return width;
}

int GraphicsHandler::getHeight()
{
	return height;
}

int GraphicsHandler::getFPS()
{
	return framespersecond;
}

bool GraphicsHandler::getVSync()
{
	return vsync;
}

const char* GraphicsHandler::getTitle()
{
	return label;
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
