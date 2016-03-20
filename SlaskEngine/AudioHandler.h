#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>
#include "Audio.h"

class AudioHandler
{
private:
	FMOD_RESULT result;
	FMOD::Studio::System* audioSys;

	int driverCount;
	int maxChannels;
	void setMaxChannels(int channels);

	bool sampleasync; 
	bool sampledecompress;

public:
	static AudioHandler* instance();

	void init(int channels);
	~AudioHandler();

	int getMaxChannels();
};

