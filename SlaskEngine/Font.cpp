#include "Font.h"



Font::Font(const char* file)
{
	font = new sf::Font;
	if (!font->loadFromFile(file))
	{
		std::string str = "Unable to load font from file \"";
		str += file;
		str += '\"';
		LogHandler::error("Font", str.c_str());
		font = NULL;
	}
}


Font::~Font()
{
	if (font)
		delete font;
}

/*

?????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????????
????????????????
*/