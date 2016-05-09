#pragma once
#include "Object.h"
#include "EngineNamespace.h"
#include <vector>
#define SLASKSCENE \
public: \
	inline static unsigned int sceneId() \
	{ \
		static unsigned int _id=_engine::obtainScnId(); \
		return _id; \
	} \
	virtual inline unsigned int id() \
	{ \
		return sceneId(); \
	} \
private:

class SlaskEngine;

class Scene
{
	friend class SlaskEngine;
private:
	std::vector<Object*> _objects;
	void _deleteObjects();
	bool _deathMark;

public:
	virtual unsigned int id();
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

	virtual void run();
};