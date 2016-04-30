#include "Object.h"
#include "SlaskEngine.h"

Object::Object()
{
	_destroyed = 0;
	_tagRunValue = 1;
	_tagDrawValue = 1;
}

Object::~Object()
{
}

void Object::_refreshTagRuns(bool value)
{
	if (value == 0)
	{
		_tagRunValue = 0;
		return;
	}
	for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
		if (!(*it)->runs())
		{
			_tagRunValue = 0;
			return;
		}
	_tagRunValue = 1;
}

void Object::_refreshTagDraws(bool value)
{
	if (value == 0)
	{
		_tagDrawValue = 0;
		return;
	}
	for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
		if (!(*it)->draws())
		{
			_tagDrawValue = 0;
			return;
		}
	_tagDrawValue = 1;
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

void Object::addTag(Tag *t)
{
	SlaskEngine::instance()->objAddTag(this, t, &_tags);
}

void Object::removeTag(Tag *t)
{
	SlaskEngine::instance()->objRemoveTag(this, t, &_tags);
}

void Object::at(double xp, double yp)
{
	x = xp;
	y = yp;
}

bool Object::_getDestroyed()
{
	return _destroyed;
}
