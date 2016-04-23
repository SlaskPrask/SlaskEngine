#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

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