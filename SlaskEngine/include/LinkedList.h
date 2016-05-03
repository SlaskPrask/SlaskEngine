#pragma once

#include "../include/ListHandle.h"

template <class T>
class LinkedList
{
	friend class ListHandle<T>;
private:
	T *_nextNode;
	T *_prevNode;

protected:
	ListHandle<T> *_listHandle;

	void _next(T *t)
	{
		_nextNode = t;
	}

	void _prev(T *t)
	{
		_prevNode = t;
	}

	void _removeHandleDown()
	{
		_listHandle = 0;
		if (_nextNode)
		_nextNode->_removeHandleDown();
	}
	
public:
	LinkedList()
	{
		_nextNode = 0;
		_prevNode = 0;
		_listHandle = 0;
	}

	T *getFirst()
	{
		if (_prevNode == 0)
			return this;
		else
			return _prevNode->getFirst();
	}

	T *getLast()
	{
		if (_nextNode == 0)
			return this;
		else
			return _nextNode->getLast();
	}

	T *getNext()
	{
		return _nextNode;
	}

	T *getPrevious()
	{
		return _prevNode;
	}

	void _add(T *t)
	{
		if (_nextNode == 0)
		{
			if (_listHandle)
			{
				_listHandle->setLast(t);
				t->_listHandle = _listHandle;
			}
			_nextNode = t;
			t->_prevNode = (T*)this;
		}
		else
			_nextNode->_add(t);
	}
	
	virtual ~LinkedList()
	{
		if (_prevNode != 0)
		_prevNode->_next(_nextNode);
		else
		if (_listHandle)
		_listHandle->setFirst(_nextNode);
		
		if (_nextNode != 0)
		_nextNode->_prev(_prevNode);
		else
		if (_listHandle)
		_listHandle->setLast(_prevNode);
	}

};
