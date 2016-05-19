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
	inline bool isRunning()
	{
		return run;
	}
	inline bool isDrawing()
	{
		return draw;
	}
	inline bool runs()//TODO: deprecated
	{
		return isRunning();
	}
	inline bool draws()//TODO: deprecated
	{
		return isDrawing();
	}
	Tag* enableRun();
	Tag* disableRun();
	Tag* enableDraw();
	Tag* disableDraw();
	Tag* enable();
	Tag* disable();
	unsigned int size();
	Object* get(unsigned int i);

	virtual ~Tag();
};