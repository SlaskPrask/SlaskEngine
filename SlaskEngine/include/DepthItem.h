#pragma once
#include "Object.h"

class DepthItem
{
private:
	DepthItem *nextNode;
	DepthItem *prevNode;
	Object *item;

protected:
	inline void next(DepthItem *t)
	{
		nextNode = t;
	}

	inline void prev(DepthItem *t)
	{
		prevNode = t;
	}
	
	DepthItem();
public:
	DepthItem(Object* i);

	inline double getDepth()
	{
		return item->_depth;
	}

	inline Object *get()
	{
		return item;
	}

	inline DepthItem *getNext()
	{
		return nextNode;
	}

	inline DepthItem *getPrevious()
	{
		return prevNode;
	}

	void moveUp();
	void moveDown();

	void addAbove(DepthItem *t);
	void addBelow(DepthItem *t);
	
	virtual ~DepthItem();
};
