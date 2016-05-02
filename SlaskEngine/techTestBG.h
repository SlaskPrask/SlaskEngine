#pragma once
#include "sources\Slask.h"

class testBG :public Object
{
	SLASKOBJECT
	int windowHeight;
	int windowWidth;

private:
	Sprite *sprite;
public:
	testBG();
};