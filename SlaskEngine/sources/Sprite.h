#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "LogHandler.h"

class Sprite //undocced
{
private:
	int w, h;
	GLuint texture;

public:
	Sprite(const char* file);
	int getWidth();
	int getHeight();
	bool bind();
	~Sprite();
};

