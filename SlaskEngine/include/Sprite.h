#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "LogHandler.h"

class GraphicsHandler;

class Sprite //undocced
{
	friend class GraphicsHandler;
private:
	int w, h;
	GLuint texture;
	bool bind();

public:
	Sprite(const char* file);
	int getWidth();
	int getHeight();
	~Sprite();
};

