#pragma once
#include "sources/Slask.h"

class techEnemy: public Object
{
private:
	int xdir,ydir;
	Sprite *sprite;
	void changeDirection();
	Timer dirTimer,blinkTimer;
	int timerDistort;
	bool blink;

public:
	void run();
	void draw();
	techEnemy();
	~techEnemy();
};