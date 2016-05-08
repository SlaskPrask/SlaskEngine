#include "../include/Sprite.h"



Sprite::Sprite(const char* file)
{
	w = 0;
	h = 0;
	{
		sf::Image image;
		if (!image.loadFromFile(file))
		{
			std::string str = "Unable to load sprite from file \"";
			str += file;
			str += '\"';
			LogHandler::error("Graphics", str.c_str());
			return;
		}
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		
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
