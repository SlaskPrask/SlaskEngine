#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;

class GraphicsHandler
{
private:
	RenderWindow* window;

public:
	GraphicsHandler(int w, int h, const char* title);
	~GraphicsHandler();

	RenderWindow* getWindow();
	void drawBegin();
	void drawEnd();
	void close();
};

