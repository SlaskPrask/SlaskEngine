#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Sprite
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

