#include <iostream>
#include <vector>
#include "Sprite.h"


#pragma once
class SpriteResource
{
private:
	typedef std::vector<Sprite*> SpriteVector;
	SpriteVector sprites;

public:
	SpriteResource();
	~SpriteResource();
};

