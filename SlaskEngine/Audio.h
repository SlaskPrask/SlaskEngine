#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

class AudioHandler;

class Audio
{
private:
	FMOD::Studio::Bank* bank;
	FMOD::Studio::System* system;
	FMOD::Studio::EventDescription* eventD;
	FMOD::Studio::EventInstance* eventInstance;

	bool sampleasync;
	bool sampledecompress;
	FMOD_RESULT result;


public:
	Audio(const char* file);
	FMOD::Studio::EventInstance* getInstance();

	~Audio();

};

