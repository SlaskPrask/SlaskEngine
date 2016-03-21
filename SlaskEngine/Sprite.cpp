#include "Sprite.h"



Sprite::Sprite(const char* file)
{
	tex = new sf::Texture();

	if (!tex->loadFromFile(file))
		tex = NULL;
}

int Sprite::getWidth()
{
	return tex->getSize().x;
}

int Sprite::getHeight()
{
	return tex->getSize().y;
}

bool Sprite::bind()
{
	if (tex)
	{
		sf::Texture::bind(tex);
			return true;
	}
	else
		return false;
}

Sprite::~Sprite()
{
	if (tex)
		delete tex;
}






//namespaces

GraphicsHandler* slask::graphics()
{
	return GraphicsHandler::instance();
}

InputHandler* slask::input()
{
	return InputHandler::instance();
}

AudioHandler* slask::audio()
{
	return AudioHandler::instance();
}