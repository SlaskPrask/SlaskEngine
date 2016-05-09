#pragma once
#include <vector>
#include "LogHandler.h"
#include "Audio.h"
#include "AudioBank.h"

class SlaskEngine;

class AudioSet //undocced
{
	friend class SlaskEngine;
private:

	AudioBank* bank;
	std::vector<Audio*> data;
	std::vector<std::string> file;
	std::string bankFile;
	unsigned int loads;
	unsigned int engine_id;
	bool _deathMark;

public:
	unsigned int add(std::string str);
	AudioSet();
	~AudioSet();
	void load();
	bool isLoaded();
	int instances();
	void unload();
	unsigned int id();
	Audio* get(unsigned int i);
	AudioBank* getBank();
	void setBank(const char* bank);
};

