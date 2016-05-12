#include "../include/DepthItem.h"
#include "../include/SlaskEngine.h"

DepthItem::DepthItem(Object* i)
{
	nextNode = 0;
	prevNode = 0;
	item = i;
	item->_depthItem = this;
}

//goes down on the list attempting to be before the given node
void DepthItem::addAbove(DepthItem *t)
{
	if (getDepth()>=t->getDepth())
	{
		prevNode=t->getPrevious();
		nextNode=t;
		if (prevNode)
		prevNode->next(this);
		nextNode->prev(this);
	}
	else
	if (t->getNext())
	{
		addAbove(t->getNext());
	}
	else
	{//highest depth, bottom node
		nextNode=0;
		prevNode=t;
		t->next(this);
	}
}

//goes up on the list attempting to be after the given node
void DepthItem::addBelow(DepthItem *t)
{
	if (getDepth()<=t->getDepth())
	{
		nextNode=t->getNext();
		prevNode=t;
		if (nextNode)
		nextNode->prev(this);
		prevNode->next(this);
	}
	else
	if (t->getPrevious())
	{
		addBelow(t->getPrevious());
	}
	else
	{//lowest depth, top node
		prevNode=0;
		nextNode=t;
		t->prev(this);
	}
}

//my depth got larger ++++
void DepthItem::moveUp()
{
	if (prevNode)
	{
		if (prevNode->getDepth()<getDepth())//move required
		{
			detach();
			addBelow(prevNode);//causes a second if but i guess it's ok
		}
	}
	//else, already top
}

//my depth got lesser ----
void DepthItem::moveDown()
{
	if (nextNode)
	{
		if (nextNode->getDepth()>getDepth())//move required
		{
			detach();
			addAbove(nextNode);//causes a second if but i guess it's ok
		}
	}
	//else, already bottom
}

void DepthItem::detach()
{
	if (prevNode)
	prevNode->next(nextNode);
	else
	{//detach from top
		SlaskEngine::instance()->setFirstDepth(nextNode);
	}
	if (nextNode)
	nextNode->prev(prevNode);
	//leaves this node with loose ends
}

DepthItem::~DepthItem()
{
	detach();
}
