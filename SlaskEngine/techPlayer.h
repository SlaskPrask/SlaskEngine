#pragma once
#include "sources\Slask.h"

class player :public Object
{
private:
	double xvel, yvel;
	double friction;
	double accel;
	double maxspeed;
	Sprite *sprite;
public:
	void run();
	void draw();

	player();
	~player();
};

