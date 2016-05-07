#pragma once

#include "LinkedList.h"
#include "Tag.h"
#include "EngineNamespace.h"
#include <vector>
#define SLASKOBJECT \
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
private:

class SlaskEngine;
class DepthItem;
class Scene;

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
	friend class DepthItem;
	friend class Scene;
private:
	Scene *_scene;
	bool _tagRunValue, _tagDrawValue;
	bool _destroyed;
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
	double x;
	double y;
	Object();
	virtual ~Object();

	virtual unsigned int id();

	inline bool isPersistent()
	{
		return _persistent;
	}

	inline Object* setPersistent();
	inline Object* unsetPersistent();

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