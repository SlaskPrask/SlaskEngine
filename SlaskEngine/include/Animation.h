#pragma once
#include "AnimationData.h"
#include "Sprite.h"

class SlaskEngine;

class Animation
{
	private:
	AnimationData *data;
	Sprite *sprite;
	double pos;
	Animation();
	inline void updateFrame(int f)
	{
		frame=f;
	}
	int frame;

	public:
	inline Sprite* getSprite()
	{
		return sprite;
	}
	inline double getWidth()
	{
		return data->getWidth(frame);
	}
	inline double getHeight()
	{
		return data->getHeight(frame);
	}
	inline double getFromX()
	{
		return data->getFromX(frame)/sprite->getWidth();
	}
	inline double getFromY()
	{
		return data->getFromY(frame)/sprite->getHeight();
	}
	inline double getToX()
	{
		return data->getToX(frame)/sprite->getWidth();
	}
	inline double getToY()
	{
		return data->getToY(frame)/sprite->getHeight();
	}
	void setPosition(double p);
	Animation(Sprite *s,AnimationData *d);
	void run();
	double getPosition();
	int getFrame();
};