#pragma once
#include "AudioHandler.h"

class AudioBus
{
private:
	FMOD::Studio::Bus* bus;

	FMOD::Studio::System* system;

	FMOD_RESULT result;


public:
	AudioBus(const char* busName);

	FMOD::Studio::Bus* getBus();
	~AudioBus();
};