#include "Sprite.h"



Sprite::Sprite(const char* file)
{
	if (tex.loadFromFile(file))
		sf::Texture::bind(&tex);
	else
		tex = NULL;
}


Sprite::~Sprite()
{
}
