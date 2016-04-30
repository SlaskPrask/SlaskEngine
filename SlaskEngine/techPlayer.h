#pragma once
#include "sources/Slask.h"

class player :public Object
{
	SLASKOBJECT
private:
	double xvel, yvel;
	double friction;
	double accel;
	double maxspeed;
	Sprite *sprite;
public:
	player();
	~player();
};

