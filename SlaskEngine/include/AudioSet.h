#pragma once
#include <vector>
#include "../include/LogHandler.h"
#include "../include/Audio.h"
#include "../include/AudioBank.h"

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

