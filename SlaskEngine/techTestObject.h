#pragma once

#include "include/Slask.h"

class TestObject :public Object
{
	SLASKOBJECT

private:
	int windowHeight, windowWidth, position;
	Sprite *sprite;
	std::vector<std::string> files;
	Font *font;

public:
	TestObject();
	~TestObject();
};