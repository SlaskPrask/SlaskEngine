#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Sprite
{
private:
	int w, h;
	sf::Texture* tex;
	

public:
	Sprite(const char* file);
	int getWidth();
	int getHeight();
	bool bind();
	~Sprite();
};

