#include "AudioHandler.h"



AudioHandler::AudioHandler(int channels)
{
	//driverCount = 0;

	result = FMOD::Studio::System::create(&audioSys);
	
	if (result != FMOD_OK)
	{
		//ERROR
		return;
	}
	
	/* audioSys->getNumDrivers(&driverCount); //doesn't work

	

	if (driverCount == 0) 
	{
		//ERROR
		return;
	}*/

	setMaxChannels(channels);

	//Initialize FMOD instance with 24 channels
	result = audioSys->initialize(channels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

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
