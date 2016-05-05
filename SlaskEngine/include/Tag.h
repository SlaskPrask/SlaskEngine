#pragma once
#include <algorithm>
#include <vector>

class SlaskEngine;
class Object;

class Tag//undocced
{
	friend class SlaskEngine;
private:
	bool run;
	bool draw;
	std::vector<Object*> _tagObjs;
	bool detachObj(Object* o);
	bool attachObj(Object* o);

public:
	Tag();
	inline bool runs()//undocced
	{
		return run;
	}
	inline bool draws()//undocced
	{
		return draw;
	}
	void enableRun();//undocced
	void disableRun();//undocced
	void enableDraw();//undocced
	void disableDraw();//undocced
	inline void enable();//undocced
	inline void disable();//undocced

	virtual ~Tag();
};