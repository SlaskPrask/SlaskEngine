#include "../include/DepthItem.h"
#include "../include/SlaskEngine.h"

DepthItem::DepthItem(Object* i)
{
	nextNode = 0;
	prevNode = 0;
	item = i;
	item->_depthItem = this;
}

void DepthItem::addAbove(DepthItem *t)
{
	if (t->getDepth() > getDepth())
	{
		if (prevNode == 0)
		{
			SlaskEngine::instance()->setFirstDepth(t);
			prevNode = t;
			t->next(this);
		}
		else
		{
			t->next(this);
			t->prev(prevNode);
			prevNode->next(t);
			prev(t);
		}
	}
	else
	{
		if (nextNode)
			nextNode->addAbove(t);
		else
		{
			t->next(nextNode);//0 end
			next(t);
			t->prev(this);
		}
	}
}

void DepthItem::addBelow(DepthItem *t)
{
	if (t->getDepth() < getDepth())
	{
		if (nextNode == 0)
		{
			nextNode = t;
			t->prev(this);
		}
		else
		{
			t->prev(this);
			t->next(nextNode);
			nextNode->prev(t);
			next(t);
		}
	}
	else
	{
		if (prevNode)
			prevNode->addBelow(t);
		else
		{
			SlaskEngine::instance()->setFirstDepth(t);
			t->prev(prevNode);//0 begin
			prev(t);
			t->next(this);
		}
	}
}

void DepthItem::moveUp()
{
	if (prevNode)
	{
		if (prevNode->getDepth() < getDepth())
		{
			prevNode->next(nextNode);
			if (nextNode)
				nextNode->prev(prevNode);
			prevNode->addBelow(this);
		}
	}
}

void DepthItem::moveDown()
{
	if (nextNode)
	{
		if (nextNode->getDepth() > getDepth())
		{
			nextNode->prev(prevNode);
			if (prevNode)
				prevNode->next(nextNode);
			else
				SlaskEngine::instance()->setFirstDepth(nextNode);
			nextNode->addAbove(this);
		}
	}
}

DepthItem::~DepthItem()
{
	if (prevNode != 0)
		prevNode->next(nextNode);
	else
		SlaskEngine::instance()->setFirstDepth(nextNode);

	if (nextNode != 0)
		nextNode->prev(prevNode);
}
