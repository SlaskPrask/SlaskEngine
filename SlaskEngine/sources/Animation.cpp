#include "../include/Animation.h"
#include "../include/SlaskEngine.h"

Animation::Animation(Sprite *s,AnimationData *d):data(d),sprite(s)
{
	pos=0;
	frame=0;
	speed=1;
}

Animation::Animation()
{
	sprite=NULL;
	data=NULL;
	pos=0;
	frame=0;
	speed=1;
}

void Animation::setSprite(Sprite *s)
{
	sprite=s;
}

void Animation::setData(AnimationData *d)
{
	data=d;
	pos=0;
	frame=0;
}

void Animation::setPosition(double p)
{
	pos=p;

	if (!data)
	{
		frame=0;
	}
	else
	{
		if (data->getDuration()>0&&data->getLoop())
			while (pos>=data->getDuration())
				pos-=data->getDuration();

		//TODO: optimize, store earlier frames duration check if pos-that is above next
		frame=data->getFrameAt(pos);
	}
}

void Animation::setSpeed(double s)
{
	speed=(s<=0?0:s);
}

void Animation::run()
{
	if (data->getRealTime())
	setPosition(pos+speed*SlaskEngine::instance()->getFrameMultiplier());
	else
	setPosition(pos+speed);
}

double Animation::getPosition()
{
	return pos;
}

int Animation::getFrame()
{
	return frame;
}
