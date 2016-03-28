#pragma once
#include <SFML/Graphics.hpp>
#include "LogHandler.h"

class Font
{
private:
	sf::Font* font;

public:
	Font(const char* file);
	~Font();
};

