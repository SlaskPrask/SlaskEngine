#pragma once
#include "Object.h"
#include <vector>

class SlaskEngine;

class Scene
{
	friend class SlaskEngine;
private:
	std::vector<Object*> _objects;
	void _deleteObjects();

public:
	int width, height;
	//void load(const char* file,int xoffset,int yoffset);
	//void load(const char* file);
	inline void setSize(int w,int h)
	{
		width = w;
		height = h;
	}
	Scene();
	virtual ~Scene();
};