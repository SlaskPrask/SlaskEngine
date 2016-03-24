#include "Font.h"



Font::Font(const char* file)
{
	font = new sf::Font;
	if (!font->loadFromFile(file));
		font = NULL;
}


Font::~Font()
{
	if (font)
		delete font;
}
