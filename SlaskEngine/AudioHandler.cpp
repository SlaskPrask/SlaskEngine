#include "AudioHandler.h"



AudioHandler::AudioHandler()
{
	if (FMOD::System_Create(&audioSys) != FMOD_OK) 
	{
		//ERROR
		return;
	}

	driverCount = 0;
	audioSys->getNumDrivers(&driverCount);

	if (driverCount == 0) 
	{
		//ERROR
		return;
	}

	setMaxChannels(12);

	//Initialize FMOD instance with 24 channels
	audioSys->init(maxChannels, FMOD_INIT_NORMAL, 0);

}

void AudioHandler::setMaxChannels(int channels)
{
	maxChannels = channels;
}

int AudioHandler::getMaxChannels()
{
	return maxChannels;
}


AudioHandler::~AudioHandler()
{
}
