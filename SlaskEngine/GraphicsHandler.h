#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;

class GraphicsHandler
{
private:
	Window* window;

public:
	GraphicsHandler(int w, int h, const char* title);
	~GraphicsHandler();

	Window* getWindow();
};

