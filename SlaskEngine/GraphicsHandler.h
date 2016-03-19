#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>


class GraphicsHandler
{
private:
	sf::RenderWindow* window;

public:
	GraphicsHandler(int w, int h, const char* title);
	~GraphicsHandler();

	sf::RenderWindow* getWindow();
	void setTitle(const char* title);
	void setFPS(int fps);
	void drawBegin();
	void drawEnd();
	void close();
};

