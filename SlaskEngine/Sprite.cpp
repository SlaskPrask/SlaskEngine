#include "Sprite.h"



Sprite::Sprite(const char* file)
{
	w = 0;
	h = 0;
	{
		sf::Image image;
		image.loadFromFile(file);
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		w = image.getSize().x;
		h = image.getSize().y;
	}
}

int Sprite::getWidth()
{
	return w;
}

int Sprite::getHeight()
{
	return h;
}

bool Sprite::bind()
{
	if (w&&h)
	{
		glBindTexture(GL_TEXTURE_2D,texture);
		return true;
	}
	else
	return false;
}

Sprite::~Sprite()
{
	if (w&&h)
	glDeleteTextures(1,&texture);
}
