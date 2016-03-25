#include "AudioHandler.h"
#include <iostream>

AudioHandler* AudioHandler::instance()
{
	static AudioHandler audiohandler;
	return &audiohandler;
}

void AudioHandler::init(int channels)
{
	
	extraDriverData = NULL;
	audioSys = NULL;
	lowLevelSys = NULL;
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
	if (result != FMOD_OK)
	{
		std::cout << "Initializing: " << FMOD_ErrorString(result) << '\n';
	}

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

/*void loadEvent(Audio* audio, const char* event)
{

}*/

void AudioHandler::play(Audio* audio)
{
	audio->getInstance()->start();
}

void AudioHandler::stop(Audio* audio)
{
	audio->getInstance()->stop(FMOD_STUDIO_STOP_IMMEDIATE);
}

void AudioHandler::run()
{
	audioSys->update();
}

void AudioHandler::pause(Audio* audio)
{
	audio->getInstance()->setPaused(true);
}

void AudioHandler::unpause(Audio* audio)
{
	audio->getInstance()->setPaused(false);
}

void AudioHandler::trigger(Audio* audio)
{
	//Makes the cursor able to move past a sustain point
	audio->getInstance()->triggerCue();
}

void AudioHandler::release(Audio* audio)
{
	//Destroys the event
	audio->getInstance()->release();
}

void AudioHandler::setVolume(Audio* audio, double vol)
{
	audio->getInstance()->setVolume((vol>1.0f ? 1.0f : (vol<0.0f ? 0.0f : vol)));;
}

void AudioHandler::setParameterValue(Audio* audio, const char* param, double value)
{
	audio->getInstance()->setParameterValue(param, value);
}

void AudioHandler::setPitch(Audio* audio, double pitch)
{
	audio->getInstance()->setPitch(pitch);
}

void AudioHandler::setTimePosition(Audio* audio, int position)
{
	//Timeline position in milliseconds
	audio->getInstance()->setTimelinePosition(position);
}


AudioHandler::~AudioHandler()
{
	audioSys->unloadAll();
	audioSys->release();
}
