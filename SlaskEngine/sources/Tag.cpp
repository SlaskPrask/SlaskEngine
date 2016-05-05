#include "../include/Tag.h"
#include "../include/Object.h"
#include "../include/SlaskEngine.h"

Tag::Tag()
{
	run = draw = 1;
}

Tag::~Tag()
{
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	SlaskEngine::instance()->objUnlinkTag((*it), this);
}

bool Tag::detachObj(Object* o)
{
	std::vector<Object*>::const_iterator it = std::find(_tagObjs.begin(), _tagObjs.end(), o);
	if (it != _tagObjs.end())
	{
		_tagObjs.erase(it);
		return 1;
	}
	return 0;
}

bool Tag::attachObj(Object* o)
{
	std::vector<Object*>::const_iterator it = std::find(_tagObjs.begin(), _tagObjs.end(), o);
	if (it == _tagObjs.end())
	{
		_tagObjs.push_back(o);
		return 1;
	}
	return 0;
}

Tag* Tag::enableRun()
{
	SlaskEngine *engine = SlaskEngine::instance();
	run = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it,1);
	return this;
}
Tag* Tag::disableRun()
{
	SlaskEngine *engine = SlaskEngine::instance();
	run = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it, 0);
	return this;
}
Tag* Tag::enableDraw()
{
	SlaskEngine *engine = SlaskEngine::instance();
	draw = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 1);
	return this;
}

Tag* Tag::disableDraw()
{
	SlaskEngine *engine = SlaskEngine::instance();
	draw = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 0);
	return this;
}

Tag* Tag::enable()
{
	SlaskEngine *engine = SlaskEngine::instance();
	run = 1;
	draw = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	{
		engine->refreshObjTagRuns(*it, 1);
		engine->refreshObjTagDraws(*it, 1);
	}
	return this;
}

Tag* Tag::disable()
{
	SlaskEngine *engine = SlaskEngine::instance();
	draw = 0;
	run = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	{
		engine->refreshObjTagRuns(*it, 0);
		engine->refreshObjTagDraws(*it, 0);
	}
	return this;
}
