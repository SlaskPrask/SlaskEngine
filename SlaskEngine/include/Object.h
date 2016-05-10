#pragma once

#include "LinkedList.h"
#include "Tag.h"
#include "EngineNamespace.h"
#include <vector>
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
		return (*(_instance()))[_pos]; \
	} \
private: \
	virtual void _addInstance(Object *inst) \
	{ \
		_instance()->push_back(inst); \
std::cout << "adding\n"; \
	} \
	virtual void _removeInstance(Object *inst) \
	{ \
		std::vector<Object*>::const_iterator it = std::find(_instance()->begin(), _instance()->end(), inst); \
		_instance()->erase(it); \
	}

class SlaskEngine;
class DepthItem;
class Scene;

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
	friend class DepthItem;
private:
	virtual void _addInstance(Object *inst);
	virtual void _removeInstance(Object *inst);
	Scene *_scene;
	bool _tagRunValue, _tagDrawValue;
	bool _destroyed;
	bool _deathMark;
	inline bool _getDestroyed()
	{
		return _destroyed;
	}
	bool _persistent;
	double _qdepth,_depth;
	std::vector<Tag*> _tags;
	inline bool _tagRuns()
	{
		return _tagRunValue;
	}
	inline bool _tagDraws()
	{
		return _tagDrawValue;
	}
	void _refreshTagRuns(bool value);
	void _refreshTagDraws(bool value);
	DepthItem *_depthItem;
	void _performDepthMove();
	inline Object* _copyDepth()
	{
		_depth = _qdepth;
		return this;
	}
	
public:
	bool visible;
	double x;
	double y;
	Object();
	virtual ~Object();

	virtual unsigned int id();

	inline bool isPersistent()
	{
		return _persistent;
	}

	inline bool isRunEnabled()
	{
		return _tagRuns();
	}
	inline bool isDrawEnabled()
	{
		return _tagDraws();
	}
	Object* setPersistent();
	Object* unsetPersistent();

	Object* addTag(Tag *tag);
	Object* removeTag(Tag *tag);
	inline Object* at(double xp, double yp)
	{
		x = xp;
		y = yp;
		return this;
	}
	inline Object* setPosition(double xp, double yp)
	{
		return at(xp, yp);
	}
	inline Object* move(double xp, double yp)
	{
		x += xp;
		y += yp;
		return this;
	}
	inline double getDepth()
	{
		return _qdepth;
	}
	inline double depth()
	{
		return getDepth();
	}
	double depth(double d);
	inline double setDepth(int d)
	{
		return depth(d);
	}
	inline void destroy()
	{
		_destroyed = true;
	}

	virtual void run();
	virtual void draw();
	virtual void runEnabled();
	virtual void runDisabled();
	virtual void drawEnabled();
	virtual void drawDisabled();
};