#pragma once
#include <fmod.hpp>
#include <fmod_errors.h> //for errors only
#include "Audio.h"

class AudioHandler
{
private:
	FMOD::System* audioSys;
	int driverCount;
	int maxChannels;
	void setMaxChannels(int channels);

public:
	AudioHandler(int channels);
	~AudioHandler();

	int getMaxChannels();
};

