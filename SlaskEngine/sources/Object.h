#pragma once

#include "LinkedList.h"

class SlaskEngine;

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
private:
	bool _destroyed;
	bool _getDestroyed();

public:
	double x;
	double y;
	Object();
	virtual ~Object();

	virtual void run();
	virtual void draw();

	void destroy();
};