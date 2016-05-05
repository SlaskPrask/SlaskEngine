#include "../include/Object.h"
#include "../include/SlaskEngine.h"
#include "../include/Scene.h"

Object::Object()
{
	_destroyed = 0;
	_tagRunValue = 1;
	_tagDrawValue = 1;
	_qdepth = _depth = 0;
	_depthItem = NULL;
	_persistent = 1;
	_scene = NULL;
	x = y = 0;
	SlaskEngine::instance()->createObject(this);
	SlaskEngine::instance()->queueDepth(this);
}

Object::~Object()
{
	for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
	SlaskEngine::instance()->objClearTag(this, *it);
	SlaskEngine::instance()->detachDepth(this);
	if (_scene)
	SlaskEngine::instance()->untieObjectFromScene(_scene, this);
}

void Object::unsetPersistent()
{
	if (_persistent)
	{
		_scene = SlaskEngine::instance()->getCurrentScene();
		if (_scene)
		{
			SlaskEngine::instance()->tieObjectToScene(_scene, this);
			_persistent = 0;
		}
		else
		{
			LogHandler::notify("Engine","Unable to unset persistence of object, no active scene.");
		}
	}
}

void Object::setPersistent()
{
	if (!_persistent)
	{
		SlaskEngine::instance()->untieObjectFromScene(_scene,this);
		_scene = NULL;
		_persistent = 0;
	}
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

void Object::_performDepthMove()
{
	if (_qdepth > _depth)
	{
		_depth = _qdepth;
		_depthItem->moveUp();
	}
	if (_qdepth < _depth)
	{
		_depth = _qdepth;
		_depthItem->moveDown();
	}
}

void Object::run()
{
}

void Object::draw()
{
}

double Object::depth(double d)
{
	_qdepth = d;
	if (_depthItem)
	SlaskEngine::instance()->queueDepthChange(this);
	return _qdepth;
}

void Object::addTag(Tag *t)
{
	SlaskEngine::instance()->objAddTag(this, t);
}

void Object::removeTag(Tag *t)
{
	SlaskEngine::instance()->objRemoveTag(this, t);
}

bool Object::_getDestroyed()
{
	return _destroyed;
}
