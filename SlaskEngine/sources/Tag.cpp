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
	if (run == 1)
		return this;

	SlaskEngine *engine = SlaskEngine::instance();
	run = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it,1);
	return this;
}
Tag* Tag::disableRun()
{
	if (run == 0)
		return this;

	SlaskEngine *engine = SlaskEngine::instance();
	run = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it, 0);
	return this;
}
Tag* Tag::enableDraw()
{
	if (draw == 1)
		return this;

	SlaskEngine *engine = SlaskEngine::instance();
	draw = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 1);
	return this;
}

Tag* Tag::disableDraw()
{
	if (draw == 0)
		return this;

	SlaskEngine *engine = SlaskEngine::instance();
	draw = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 0);
	return this;
}

Tag* Tag::enable()
{
	if (run == 1 && draw == 1)
		return this;

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
	if (run == 0 && draw == 0)
		return this;

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

unsigned int Tag::size()
{
	unsigned int count=0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	if (!SlaskEngine::instance()->isObjectDestroyed(*it))
	count++;
	return count;
}

Object* Tag::get(unsigned int i)
{
	unsigned int count=-1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	if (!SlaskEngine::instance()->isObjectDestroyed(*it))
	{
		count++;
		if (count==i)
		return *it;
	}

	return NULL;
}
