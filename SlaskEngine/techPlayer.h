#pragma once
#include "include/Slask.h"

class player :public Object
{
	SLASKOBJECT
private:
	double xvel, yvel;
	double friction;
	double accel;
	double maxspeed;
	Sprite *sprite;
	Camera cam;
public:
	player();
	~player();
};

