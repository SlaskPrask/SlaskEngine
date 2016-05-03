#pragma once

#include "../include/LinkedList.h"
#include "../include/Tag.h"
#include <vector>
#define SLASKOBJECT \
public: \
	void run(); \
	void draw(); \
private:

class SlaskEngine;

class Object : public LinkedList<Object>
{
	friend class SlaskEngine;
private:
	bool _tagRunValue, _tagDrawValue;
	bool _destroyed;
	bool _getDestroyed();
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
	
public:
	double x;
	double y;
	Object();
	virtual ~Object();

	void addTag(Tag *t);//undocced
	void removeTag(Tag *t);//undocced
	void at(double xp, double yp)//undocced
	{
		x = xp;
		y = yp;
	}
	inline void destroy()//undocced
	{
		_destroyed = true;
	}

	virtual void run();
	virtual void draw();
};