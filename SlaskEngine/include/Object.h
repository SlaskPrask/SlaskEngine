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

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
	friend DepthItem;
private:
	bool _tagRunValue, _tagDrawValue;
	bool _destroyed;
	bool _getDestroyed();
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
	
public:
	double x;
	double y;
	Object();
	virtual ~Object();

	void addTag(Tag *t);//undocced
	void removeTag(Tag *t);//undocced
	inline void at(double xp, double yp)//undocced
	{
		x = xp;
		y = yp;
	}
	inline void setPosition(double xp, double yp)//undocced
	{
		at(xp, yp);
	}
	inline void move(double xp, double yp)//undocced
	{
		x += xp;
		y += yp;
	}
	inline double getDepth()//undocced
	{
		return _qdepth;
	}
	inline double depth()//undocced
	{
		return getDepth();
	}
	double depth(double d);//undocced
	inline int setDepth(int d)//undocced
	{
		depth(d);
	}
	inline void destroy()//undocced
	{
		_destroyed = true;
	}

	virtual void run();
	virtual void draw();
};