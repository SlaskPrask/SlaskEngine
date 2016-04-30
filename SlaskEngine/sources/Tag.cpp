#include "Tag.h"
#include "Object.h"
#include "SlaskEngine.h"

Tag::Tag()
{
	run = draw = 1;
}

Tag::~Tag()
{
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
		(*it)->removeTag(this);
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

void Tag::enableRun()
{
	SlaskEngine *engine = SlaskEngine::instance();
	run = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it,1);
}
void Tag::disableRun()
{
	SlaskEngine *engine = SlaskEngine::instance();
	run = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagRuns(*it, 0);
}
void Tag::enableDraw()
{
	SlaskEngine *engine = SlaskEngine::instance();
	draw = 1;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 1);
}
void Tag::disableDraw()
{
	SlaskEngine *engine = SlaskEngine::instance();
	draw = 0;
	for (std::vector<Object*>::iterator it = _tagObjs.begin(); it != _tagObjs.end(); ++it)
	engine->refreshObjTagDraws(*it, 0);
}
