#pragma once
#include "sources/Slask.h"

class techEnemy
{
private:
	int xdir,ydir;
	Sprite *sprite;
	void changeDirection();
	Timer *dirTimer;

public:
	void run();
	void draw();
	techEnemy();
	~techEnemy();
};