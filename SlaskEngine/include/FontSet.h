#pragma once
#include <vector>
#include "LogHandler.h"
#include "Font.h"

class SlaskEngine;

class FontSet //undocced
{
	friend class SlaskEngine;
private:
	std::vector<Font*> data;
	std::vector<std::string> file;
	unsigned int loads;
	unsigned int engine_id;
	bool _deathMark;

public:
	unsigned int add(std::string str);
	FontSet();
	~FontSet();
	void load();
	bool isLoaded();
	int instances();
	void unload();
	unsigned int id();
	Font* get(unsigned int i);
};
