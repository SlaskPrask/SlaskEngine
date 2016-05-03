#pragma once
#include "../include/GraphicsHandler.h"

class SlaskEngine;

class Camera
{
	friend class SlaskEngine;
private:
	double x, y;
	double w, h;
	double boundsLeft, boundsRight, boundsTop, boundsBottom;
	double limitsLeft, limitsRight, limitsTop, limitsBottom;
	double *followx, *followy;
	void doFollow();
	void init();
	inline void checkXLimits()
	{
		if (x<limitsLeft)
			x = limitsLeft;
		else
			if (x+w>limitsRight)
				x = limitsRight-w;
	}
	inline void checkYLimits()
	{
		if (y<limitsTop)
			y = limitsTop;
		else
			if (y+h>limitsBottom)
				y = limitsBottom-h;
	}
public:
	Camera();//undocced
	Camera(double xp, double yp, double sw, double sh);//undocced

	inline void at(double xp, double yp)//undocced
	{
		x = xp;
		y = yp;
	}
	inline void setPosition(double xp, double yp)//undocced
	{
		at(xp, yp);
	}
	inline void setX(double p)//undocced
	{
		x = p;
	}
	inline void setY(double p)//undocced
	{
		y = p;
	}
	inline void unfollow()//undocced
	{
		followx = followy = NULL;
	}
	bool isFollowing()//undocced
	{
		return (followx==NULL?0:1);
	}
	void follow(double *xpoint, double *ypoint)//undocced
	{
		followx = xpoint;
		followy = ypoint;
	}
	inline double getBoundsTop()//undocced
	{
		return boundsTop;
	}
	inline double getBoundsLeft()//undocced
	{
		return boundsLeft;
	}
	inline double getBoundsRight()//undocced
	{
		return boundsRight;
	}
	inline double getBoundsBottom()//undocced
	{
		return boundsBottom;
	}
	inline double getLimitsTop()//undocced
	{
		return limitsTop;
	}
	inline double getLimitsLeft()//undocced
	{
		return limitsLeft;
	}
	inline double getLimitsRight()//undocced
	{
		return limitsRight;
	}
	inline double getLimitsBottom()//undocced
	{
		return limitsBottom;
	}
	void setBounds(double left, double top, double right, double bottom);//undocced
	void setLimits(double left, double top, double right, double bottom);//undocced

	void setSize(double sw, double sh);//undocced
	
	inline bool isActive()//undocced
	{
		return (GraphicsHandler::instance()->getCamera() == this);
	}
	inline void activate()//undocced
	{
		GraphicsHandler::instance()->setCamera(this);
	}
	inline double getX()//undocced
	{
		return x;
	}
	inline double getLeft()//undocced
	{
		return x;
	}
	inline double getY()//undocced
	{
		return y;
	}
	inline double getTop()//undocced
	{
		return y;
	}
	inline double getWidth()//undocced
	{
		return w;
	}
	inline double getHeight()//undocced
	{
		return h;
	}
	inline double getRight()//undocced
	{
		return x+w;
	}
	inline double getBottom()//undocced
	{
		return y+h;
	}

	~Camera();
};