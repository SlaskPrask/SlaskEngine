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
	_deathMark = 0;
	_scene = NULL;
	x = y = 0;
	SlaskEngine::instance()->createObject(this);
	SlaskEngine::instance()->queueDepth(this);
}

Object::~Object()
{
	if (!_deathMark)
	LogHandler::error("Engine", "delete called on an Object. Use ->destroy() instead.");
	
	for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
	SlaskEngine::instance()->objClearTag(this,*it);
	SlaskEngine::instance()->detachDepth(this);
	if (_scene)
	SlaskEngine::instance()->untieObjectFromScene(_scene, this);
}

unsigned int Object::id()
{
	return 0;
}

Object* Object::unsetPersistent()
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
	return this;
}

Object* Object::setPersistent()
{
	if (!_persistent)
	{
		SlaskEngine::instance()->untieObjectFromScene(_scene,this);
		_scene = NULL;
		_persistent = 1;
	}
	return this;
}

void Object::_refreshTagRuns(bool value)
{
	if (value == 0)
	{
		if (_tagRunValue == 1 && !_getDestroyed())
			runDisabled();
		_tagRunValue = 0;
		return;
	}
	if (_tagRunValue == 0)
	{
		for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
		if (!(*it)->runs())
		return;

		if (_tagRunValue == 0 && !_getDestroyed())
			runEnabled();
		_tagRunValue = 1;
	}
}

void Object::_refreshTagDraws(bool value)
{
	if (value == 0)
	{
		if (_tagDrawValue == 1 && !_getDestroyed())
			drawDisabled();
		_tagDrawValue = 0;
		return;
	}
	if (_tagDrawValue == 0)
	{
		for (std::vector<Tag*>::iterator it = _tags.begin(); it != _tags.end(); ++it)
		if (!(*it)->draws())
		return;

		if (_tagDrawValue == 0 && !_getDestroyed())
		drawEnabled();
		_tagDrawValue = 1;
	}
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

Object* Object::addTag(Tag *t)
{
	SlaskEngine::instance()->objAddTag(this, t);
	return this;
}

Object* Object::removeTag(Tag *t)
{
	SlaskEngine::instance()->objRemoveTag(this, t);
	return this;
}

void Object::runEnabled()
{
}
void Object::runDisabled()
{
}
void Object::drawEnabled()
{
}
void Object::drawDisabled()
{
}