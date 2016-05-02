#pragma once
#include <algorithm>
#include <vector>

class SlaskEngine;
class Object;

class Tag
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
	void enableRun();
	void disableRun();
	void enableDraw();
	void disableDraw();

	virtual ~Tag();
};