#include "Object.h"

Object::Object()
{
	_destroyed = false;
}

Object::~Object()
{
}

void Object::run()
{
}

void Object::draw()
{
}

void Object::destroy()
{
	_destroyed = true;
}

bool Object::_getDestroyed()
{
	return _destroyed;
}
