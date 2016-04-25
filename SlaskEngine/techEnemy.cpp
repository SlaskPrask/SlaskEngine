#include "techEnemy.h"
using namespace slask;

techEnemy::techEnemy()
{
	sprite = getSprite(1, 0);
	changeDirection();
	dirTimer = new Timer();
	dirTimer->start();
}

void techEnemy::changeDirection()
{
	xdir = random(1) * 2 - 1;
	ydir = random(1) * 2 - 1;
}

void techEnemy::run()
{
	x += xdir
	y += ydir;

	if (dirTimer->getTime() > 60)
	{
		changeDirection();
		dirTimer->start();
	}
}

void techEnemy::draw()
{
	drawSprite(sprite, x, y, 50, 50,-99);
}

techEnemy::~techEnemy()
{
	delete dirTimer;
}