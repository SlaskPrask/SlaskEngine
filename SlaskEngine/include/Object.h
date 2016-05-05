#pragma once

#include "LinkedList.h"
#include "Tag.h"
#include <vector>
#define SLASKOBJECT \
public: \
	void run(); \
	void draw(); \
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
	bool _getDestroyed();
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

	inline bool isPersistent()
	{
		return _persistent;
	}

	inline void setPersistent();
	inline void unsetPersistent();

	void addTag(Tag *tag);
	void removeTag(Tag *tag);
	inline void at(double xp, double yp)
	{
		x = xp;
		y = yp;
	}
	inline void setPosition(double xp, double yp)
	{
		at(xp, yp);
	}
	inline void move(double xp, double yp)
	{
		x += xp;
		y += yp;
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
};