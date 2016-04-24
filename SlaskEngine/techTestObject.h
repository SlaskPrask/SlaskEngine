#pragma once

#include "sources/Slask.h"

class TestObject :public Object
{
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
	void run();
	void draw();
	TestObject();
	~TestObject();
};