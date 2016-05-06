#pragma once
#include "include/Slask.h"

class Player :public Object
{
	SLASKOBJECT
private:
	double xvel, yvel;
	double friction;
	double accel;
	double maxspeed;
	Sprite *sprite;
	Camera cam;
	bool failsafe;
public:
	Player();
	~Player();
};

