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
	if (getKey(Key::Right))
		xvel = xvel + accel < maxspeed ? xvel + accel : maxspeed;
	else
		if (getKey(Key::Left))
			xvel = xvel - accel > -maxspeed ? xvel - accel : -maxspeed;
		else
			xvel = (xvel < 0 ? -xvel : xvel) < friction ? 0 : xvel - accel*(xvel < 0 ? -1 : 1);

	if (getKey(Key::Down))
		yvel = yvel + accel < maxspeed ? yvel + accel : maxspeed;
	else
		if (getKey(Key::Up))
			yvel = yvel - accel > -maxspeed ? yvel - accel : -maxspeed;
		else
			yvel = (yvel < 0 ? -yvel : yvel) < friction ? 0 : yvel - accel*(yvel < 0 ? -1 : 1);

	x += xvel;
	y += yvel;
}

void player::draw()
{
	drawSprite(sprite,x,y,-100);
}

player::~player()
{
}
