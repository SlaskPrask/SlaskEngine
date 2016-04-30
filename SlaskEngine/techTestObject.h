#pragma once

#include "sources/Slask.h"

class TestObject :public Object
{
	SLASKOBJECT

private:
	int windowHeight, windowWidth, position;
	Sprite *sprite;
	Font *testF;
	AudioBank *TestMB;
	AudioBank *TestMSB;
	Audio *Team10;
	Audio *Guitar;
	std::vector<std::string> files;

public:
	Tag *taggy,*taggy2;

	TestObject();
	~TestObject();
};