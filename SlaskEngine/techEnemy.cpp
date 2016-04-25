#include "techEnemy.h"
using namespace slask;

techEnemy::techEnemy()
{
	sprite = getSprite(1, 0);
	changeDirection();
	dirTimer.start();
	blinkTimer.start();
	x = 200+random(getWindowWidth()-400);
	y = 200 + random(getWindowHeight() - 400);
	timerDistort = random(600);
	blink = 0;
}

void techEnemy::changeDirection()
{
	xdir = random(2) - 1;
	ydir = random(2) - 1;
}

void techEnemy::run()
{
	x += xdir;
	y += ydir;

	if (getMousePress(Mouse::Mouse1) && getMouseX() <= x + 25 && getMouseX() > x - 25 && getMouseY() <= y + 25 && getMouseY() > y - 25)
		destroy();

	if (blinkTimer.getTime() > 50)
	{
		blinkTimer.restart();
		blink = !blink;
	}

	if (dirTimer.getTime() > 400 + timerDistort)
	{
		changeDirection();
		dirTimer.restart();
		timerDistort = random(600);
	}
}

void techEnemy::draw()
{
	drawSpriteExt(sprite, x - 25, y - 25, 50, 50, 0, 0, 1, 1, 0, 0, blink*0.2f, 1, 1, -99);
}

techEnemy::~techEnemy()
{
}