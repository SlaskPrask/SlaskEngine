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
	setSize(w, h);
	setRenderSize(w, h);
	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 0);
	glFogf(GL_FOG_END, 0);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_DENSITY, 1);
	glDisable(GL_FOG);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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

void GraphicsHandler::setRenderSize(int w, int h) 
{
	int size = (w<h ? w : h);
	int offset = (w<h ? h - w : w - h);
	glViewport((w<h ? 0 : offset / 2), (w<h ? offset / 2 : 0), size, size);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
