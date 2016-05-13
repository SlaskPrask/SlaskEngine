#pragma once

#include "LinkedList.h"
#include "Tag.h"
#include "EngineNamespace.h"
#include <vector>

/*
ENGINE-ERROR: calling delete will break instance grabbing as the object pops out of the list but won't roll back
              destroy() is safe
*/

#define SLASKOBJECT \
private: \
	static std::vector<Object*>* _instance() \
	{ \
		static std::vector<Object*> i; \
		return &i; \
	} \
	static unsigned int _instPos(bool f) \
	{ \
		static unsigned int i; \
		return (f?++i:i=0); \
	} \
	static void _addInstance(Object *inst) \
	{ \
		_instance()->push_back(inst); \
	} \
	static void _removeInstance(Object *inst) \
	{ \
		std::vector<Object*>::const_iterator it = std::find(_instance()->begin(), _instance()->end(), inst); \
		_instance()->erase(it); \
	} \
public: \
	inline static unsigned int objectId() \
	{ \
		static unsigned int _id=_engine::obtainObjId(); \
		return _id; \
	} \
	virtual inline unsigned int id() \
	{ \
		return objectId(); \
	} \
	static Object* instance() \
	{ \
		if (_instance()->empty()) \
		return NULL; \
		return (*_instance())[_instPos(0)]; \
	} \
	static Object* nextInstance() \
	{ \
		unsigned int _pos=_instPos(1); \
		if (_pos>=_instance()->size()) \
		return NULL; \
		if (_engine::isObjectDestroyed((*(_instance()))[_pos])) \
		return nextInstance(); \
		return (*(_instance()))[_pos]; \
	} \
	void* operator new(size_t size) \
	{ \
		void *p=malloc(size); \
		if (!p) \
		throw std::bad_alloc(); \
		_addInstance(static_cast<Object*>(p)); \
		return p; \
	} \
	void operator delete(void *p) \
	{ \
		_removeInstance(static_cast<Object*>(p)); \
		std::free(p); \
	} \
private:

class SlaskEngine;
class DepthItem;
class Scene;

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
	friend class DepthItem;
private:
	//add instance to instance list (operator new)
	virtual void _addInstance(Object *inst);
	//remove instance from instance list (operator delete)
	virtual void _removeInstance(Object *inst);
	//attached scene
	Scene *_scene;
	//buffer of enabled states
	bool _tagRunValue, _tagDrawValue;
	//destroyed tag
	bool _destroyed;
	//delete was called by engine
	bool _deathMark;
	//get safe destruction
	inline bool _getDestroyed()
	{
		return _destroyed;
	}
	//not attached to a sceen
	bool _persistent;
	//depth to change to once queue activated, current active depth on this frame
	double _qdepth,_depth;
	//attached tags for removing
	std::vector<Tag*> _tags;
	//iterate tags and check for true value, no initial check
	void _refreshTagRuns(bool value);
	//iterate tags and check for true value, no initial check
	void _refreshTagDraws(bool value);
	//attached linked depth list
	DepthItem *_depthItem;
	//engine initiated depth queue iteration
	void _performDepthMove();
	//engine initiated depth queue iteration, copy depth before solving
	inline Object* _copyDepth()
	{
		_depth = _qdepth;
		return this;
	}
	
public:
	//personal draw disabling
	bool visible;
	//position
	double x;
	double y;
	//const, dest
	Object();
	virtual ~Object();

	//return instance id by calling static objectId
	virtual unsigned int id();
	//return persistence
	inline bool isPersistent()
	{
		return _persistent;
	}
	//return run state
	inline bool isRunEnabled()
	{
		return _tagRunValue;
	}
	//return draw state
	inline bool isDrawEnabled()
	{
		return _tagDrawValue;
	}
	//set persistence
	Object* setPersistent();
	//unset persistence
	Object* unsetPersistent();
	//add tag
	Object* addTag(Tag *tag);
	//remove tag
	Object* removeTag(Tag *tag);
	//position
	inline Object* at(double xp, double yp)
	{
		x = xp;
		y = yp;
		return this;
	}
	//at() alias
	inline Object* setPosition(double xp, double yp)
	{
		return at(xp, yp);
	}
	//move
	inline Object* move(double xp, double yp)
	{
		x += xp;
		y += yp;
		return this;
	}
	//return depth
	inline double getDepth()
	{
		return _qdepth;
	}
	//getDepth() alias
	inline double depth()
	{
		return getDepth();
	}
	//change depth
	double depth(double d);
	//depth() alias
	inline double setDepth(int d)
	{
		return depth(d);
	}
	//safe destroy this object
	inline void destroy()
	{
		_destroyed = true;
	}
	//called per frame in run
	virtual void run();
	//called per frame in draw
	virtual void draw();
	//called upon tag changing run to 1
	virtual void runEnabled();
	//called upon tag changing run to 0
	virtual void runDisabled();
	//called upon tag changing draw to 1
	virtual void drawEnabled();
	//called upon tag changing draw to 0
	virtual void drawDisabled();
};