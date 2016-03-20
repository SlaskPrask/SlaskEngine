#pragma once
#include <fmod.hpp>
#include <fmod_errors.h> //for errors only

class AudioHandler
{
private:
	FMOD::System* audioSys;
	int driverCount;
	int maxChannels;

public:
	AudioHandler();
	~AudioHandler();

	void setMaxChannels(int channels);
	
	int getMaxChannels();
};

