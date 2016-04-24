#include <iostream>
#include <vector>
#include "Sprite.h"
#include "Font.h"


#pragma once
class SpriteResource
{
private:
	typedef std::vector<Sprite*> SpriteVector;
	SpriteVector sprites;

	typedef std::vector<Font*> FontVector;
	FontVector fonts;

public:
	SpriteResource();
	~SpriteResource();
};

