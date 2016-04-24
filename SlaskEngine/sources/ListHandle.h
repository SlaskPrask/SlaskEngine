#pragma once

template <class T>
class LinkedList;

template <class T>
class ListHandle
{
	friend class LinkedList<T>;
private:
	LinkedList<T> *firstNode;
	LinkedList<T> *lastNode;

	void setFirst(T *t)
	{
		firstNode = t;
	}

	void setLast(T *t)
	{
		lastNode = t;
	}

public:
	LinkedList<T> *first()
	{
		return firstNode;
	}
	LinkedList<T> *last()
	{
		return lastNode;
	}

	void add(T* t)
	{
		if (lastNode)
			lastNode->_add(t);
		else
		{
			t->_listHandle = this;
			firstNode = t;
			lastNode = t;
		}
	}
	
	ListHandle()
	{
		firstNode = 0;
		lastNode = 0;
	}

	~ListHandle()
	{
		if (firstNode)
		{
			firstNode->_removeHandleDown();
		}
	}
};