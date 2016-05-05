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
	inline bool runs()
	{
		return run;
	}
	inline bool draws()
	{
		return draw;
	}
	Tag* enableRun();
	Tag* disableRun();
	Tag* enableDraw();
	Tag* disableDraw();
	Tag* enable();
	Tag* disable();

	virtual ~Tag();
};