#pragma once
#include <SFML/Graphics.hpp>

class Font
{
private:
	sf::Font* font;

public:
	Font(const char* file);
	~Font();
};

