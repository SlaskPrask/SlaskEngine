#include "techPlayer.h"

using namespace slask;

player::player()
{
	x = 100;
	y = 100;
	xvel = yvel = 0;
	friction = 0.5;
	accel = 0.2;
	maxspeed = 10;
	sprite = getSprite(0,0);
}

void player::run()
{
	if (getKeyHeld(Key::Right))
		xvel = xvel + accel < maxspeed ? xvel + accel : maxspeed;
	else
		if (getKeyHeld(Key::Left))
			xvel = xvel - accel > -maxspeed ? xvel - accel : -maxspeed;
		else
			xvel = (xvel < 0 ? -xvel : xvel) < friction ? 0 : xvel - accel*(xvel < 0 ? -1 : 1);

	if (getKeyHeld(Key::Down))
		yvel = yvel + accel < maxspeed ? yvel + accel : maxspeed;
	else
		if (getKeyHeld(Key::Up))
			yvel = yvel - accel > -maxspeed ? yvel - accel : -maxspeed;
		else
			yvel = (yvel < 0 ? -yvel : yvel) < friction ? 0 : yvel - accel*(yvel < 0 ? -1 : 1);

	x += xvel;
	y += yvel;
}

void player::draw()
{
	drawSpriteExt(sprite, x - 50, y - 50, 100, 100, 0, 0, 1, 1, 0, 1, 1, 0, 1, -100);
}

player::~player()
{
}
