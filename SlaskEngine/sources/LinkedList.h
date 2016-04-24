#pragma once

template <class T>
class LinkedList
{
private:
	T* _nextNode;
	T* _prevNode;

	void _next(T* t)
	{
		_nextNode = t;
	}

	void _previous(T* t)
	{
		_prevNode(t);
	}
	
public:
	LinkedList()
	{
		_nextNode = NULL;
		_prevNode = NULL;
	}

	T* getFirst()
	{
		if (prevNode == NULL)
			return this;
		else
			return _prevNode->getFirst();
	}

	T* getLast()
	{
		if (_nextNode == NULL)
			return this;
		else
			return _nextNode->getLast();
	}

	T* getNext()
	{
		return _nextNode;
	}

	T* getPrevious()
	{
		return _prevNode;
	}

	void _add(T *t)
	{
		if (_nextNode != NULL)
			_nextNode = t;
		else
			_nextNode->add(t);
	}
	
	virtual ~LinkedList()
	{
		if (_prevNode != NULL)
			_prevNode->_next(_nextNode);
		if (_nextNode != NULL)
			_nextNode->prev(_prevNode);
	}

};
