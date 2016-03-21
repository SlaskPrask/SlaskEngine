#include "AudioHandler.h"

AudioHandler* AudioHandler::instance()
{
	static AudioHandler audiohandler;
	return &audiohandler;
}

void AudioHandler::init(int channels)
{
	FMOD_RESULT result;
	//driverCount = 0;

	audioSys = 0;
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

	//Initialize FMOD instance with 12 channels
	result = audioSys->initialize(channels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

	setSampleASync(false); 
	setSampleDecompress(false);
}

void AudioHandler::setMaxChannels(int channels)
{
	maxChannels = channels;
}

int AudioHandler::getMaxChannels()
{
	return maxChannels;
}

void AudioHandler::setSampleDecompress(bool enabled)
{
	sampledecompress = enabled;
}
void AudioHandler::setSampleASync(bool enabled)
{
	sampleasync = enabled;
}

FMOD::Studio::System* AudioHandler::getSystem()
{
	return audioSys;
}

AudioHandler::~AudioHandler()
{
}
