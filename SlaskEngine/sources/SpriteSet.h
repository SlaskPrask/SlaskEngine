#pragma once
#include <vector>
#include "LogHandler.h"
#include "Sprite.h"

class SlaskEngine;

class SpriteSet
{
	friend class SlaskEngine;
private:
	std::vector<Sprite*> data;
	std::vector<std::string> file;
	unsigned int loads;
	unsigned int engine_id;

public:
	unsigned int add(std::string str);
	SpriteSet();
	~SpriteSet();
	void load();
	bool isLoaded();
	int instances();
	void unload();
	unsigned int id();
	Sprite* get(unsigned int i);
};
