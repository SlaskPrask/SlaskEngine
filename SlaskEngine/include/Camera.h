#pragma once
#include "Object.h"
#include "GraphicsHandler.h"

class SlaskEngine;

class Camera
{
	friend class SlaskEngine;
private:
	double w, h;
	double boundsLeft, boundsRight, boundsTop, boundsBottom;
	double limitsLeft, limitsRight, limitsTop, limitsBottom;
	bool limits, bounds;
	double *followx, *followy;
	void doFollow();
	void init();
	inline void checkXLimits()
	{
		if (limits)
		if (x<limitsLeft)
			x = limitsLeft;
		else
			if (x+w>limitsRight)
				x = limitsRight-w;
	}
	inline void checkYLimits()
	{
		if (limits)
		if (y<limitsTop)
			y = limitsTop;
		else
			if (y+h>limitsBottom)
				y = limitsBottom-h;
	}
public:
	double x, y;

	Camera();
	Camera(double xp, double yp, double sw, double sh);
	inline void at(double xp, double yp)
	{
		x = xp;
		y = yp;
		checkXLimits();
		checkYLimits();
	}
	inline void setPosition(double xp, double yp)
	{
		at(xp, yp);
	}
	inline void setPositionCentered(double xp, double yp)
	{
		at(xp - w / 2, yp - h / 2);
	}
	inline void setPositionCentered(Object *obj)
	{
		at(obj->x - w / 2, obj->y - h / 2);
	}
	inline void unfollow()
	{
		followx = followy = NULL;
	}
	inline bool isFollowing()
	{
		return (followx==NULL?0:1);
	}
	inline void follow(double *xpoint, double *ypoint)
	{
		followx = xpoint;
		followy = ypoint;
	}
	inline void follow(Object *obj)
	{
		followx = &(obj->x);
		followy = &(obj->y);
	}
	inline double getBoundsTop()
	{
		return boundsTop;
	}
	inline double getBoundsLeft()
	{
		return boundsLeft;
	}
	inline double getBoundsRight()
	{
		return boundsRight;
	}
	inline double getBoundsBottom()
	{
		return boundsBottom;
	}
	inline double getLimitsTop()
	{
		return limitsTop;
	}
	inline double getLimitsLeft()
	{
		return limitsLeft;
	}
	inline double getLimitsRight()
	{
		return limitsRight;
	}
	inline double getLimitsBottom()
	{
		return limitsBottom;
	}
	void setBounds(double left, double top, double right, double bottom);
	void setLimits(double left, double top, double right, double bottom);
	inline void setBounds(double hor, double ver)
	{
		setBounds(hor, ver, hor, ver);
	}
	inline void setLimits(double right, double bottom)
	{
		setLimits(0, 0, right, bottom);
	}
	void setSize(double sw, double sh);
	
	inline bool isActive()
	{
		return (GraphicsHandler::instance()->getCamera() == this);
	}
	inline void activate()
	{
		GraphicsHandler::instance()->setCamera(this);
	}
	inline double getLeft()
	{
		return x;
	}
	inline double getTop()
	{
		return y;
	}
	inline double getWidth()
	{
		return w;
	}
	inline double getHeight()
	{
		return h;
	}
	inline double getRight()
	{
		return x+w;
	}
	inline double getBottom()
	{
		return y+h;
	}
	inline void unsetLimits()
	{
		limits = 0;
	}

	~Camera();
};