#pragma once
#include <SFML/Graphics.hpp>
#include "LogHandler.h"

class Font //undocced
{
private:
	sf::Font* font;

public:
	Font(const char* file);
	~Font();
};

