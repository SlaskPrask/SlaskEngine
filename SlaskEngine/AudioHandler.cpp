#include "AudioHandler.h"
#include <iostream>

AudioHandler* AudioHandler::instance()
{
	static AudioHandler audiohandler;
	return &audiohandler;
}

void AudioHandler::init(int channels)
{
	
	extraDriverData = 0;
	audioSys = 0;
	lowLevelSys = 0;
	result = FMOD::Studio::System::create(&audioSys);

	if (result != FMOD_OK)
	{
		//ERROR
		return;
	}


	//Low Level stuff

	
	result = audioSys->getLowLevelSystem(&lowLevelSys);
	if (result != FMOD_OK)
	{
		return;
	}

	result = (lowLevelSys->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0));

	if (result != FMOD_OK)
	{
		return;
	}


	//Cool Stuff
	setMaxChannels(channels);

	//Initialize FMOD instance with 12 channels
	result = audioSys->initialize(channels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);


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

void AudioHandler::setEventFile(const char* file)
{
	eventFile = file;
}

const char* AudioHandler::getEventFile()
{
	return eventFile;
}

FMOD::Studio::EventDescription* AudioHandler::getEventDescription()
{
	return eventD;
}
FMOD::Studio::EventInstance* AudioHandler::getEventInstance()
{
	return eventInstance;
}


void AudioHandler::playAudio()
{
	result = audioSys->getEvent(eventFile, &eventD);
	if (result != FMOD_OK)
		std::cout << "Getting event: " << FMOD_ErrorString(result) << '\n';

	eventInstance = NULL;
	result = eventD->createInstance(&eventInstance);
	if (result != FMOD_OK)
		std::cout << "Creating instance: " << FMOD_ErrorString(result) << '\n';

}

AudioHandler::~AudioHandler()
{

}
