#include "../include/Animation.h"
#include "../include/SlaskEngine.h"

Animation::Animation(Sprite *s,AnimationData *d):data(d),sprite(s)
{
	pos=0;
	frame=0;
}

void Animation::setPosition(double p)
{
	pos=p;

	if (data->getDuration()>0&&data->getLoop())
		while (pos>=data->getDuration())
			pos-=data->getDuration();

	//TODO: optimize, store earlier frames duration check if pos-that is above next
	frame=data->getFrameAt(pos);
}

void Animation::run()
{
	if (data->getRealTime())
	setPosition(pos+SlaskEngine::instance()->getFrameMultiplier());
	else
	setPosition(pos+1);
}

double Animation::getPosition()
{
	return pos;
}

int Animation::getFrame()
{
	return frame;
}
