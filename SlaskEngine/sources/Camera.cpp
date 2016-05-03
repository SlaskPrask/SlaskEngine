#include "../include/Camera.h"
#include "../include/GraphicsHandler.h"

void Camera::init()
{
	followx = followy = NULL;
	boundsLeft = boundsRight = boundsTop = boundsBottom = 0;
	limitsLeft = limitsRight = limitsTop = limitsBottom = 0;
}

Camera::Camera()
{
	x = y = 0;
	w = h = 1;
	init();
}

Camera::Camera(double xp, double yp, double sw, double sh) :x(xp), y(yp), w(sw), h(sh)
{
	init();
}

void Camera::doFollow()
{
	if (isFollowing())
	{
		if (boundsLeft+boundsRight>=w)
		{
			x = *followx - w/2;
			checkXLimits();
		}
		else
		if (*followx < x + boundsLeft)
		{
			x = *followx - boundsLeft;
			checkXLimits();
		}
		else
		if (*followx > x + w - boundsRight)
		{
			x = *followx - w + boundsRight;
			checkXLimits();
		}

		if (boundsTop+ boundsBottom >= h)
		{
			h = *followy - h / 2;
			checkYLimits();
		}
		else
		if (*followy < y + boundsTop)
		{
			y = *followy - boundsTop;
			checkYLimits();
		}
		else
			if (*followy > y + h - boundsBottom)
			{
				y = *followy - h + boundsBottom;
				checkYLimits();
			}
	}
}

void Camera::setSize(double sw,double sh)
{
	w = sw;
	h = sh;
	if (isActive())
		GraphicsHandler::instance()->refreshCamera();
}

void Camera::setBounds(double left, double top, double right, double bottom)
{
	boundsLeft = left;
	boundsRight = right;
	boundsTop = top;
	boundsBottom = bottom;
}

void Camera::setLimits(double left, double top, double right, double bottom)
{
	limitsLeft = left;
	limitsRight = right;
	limitsTop = top;
	limitsBottom = bottom;
}

Camera::~Camera()
{
	if (isActive())
	GraphicsHandler::instance()->setCamera(0);
}
