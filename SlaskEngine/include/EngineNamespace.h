#pragma once

class Object;

namespace _engine
{
	inline unsigned int obtainObjId()
	{
		static unsigned int id = 1;
		return id++;
	}
	inline unsigned int obtainScnId()
	{
		static unsigned int id = 1;
		return id++;
	}
	bool isObjectDestroyed(Object* o);
}
