#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

class AudioHandler;

class Audio
{
	friend class AudioHandler;
private:
	FMOD::Studio::Bank* bank;
	FMOD::Studio::System* system;
	FMOD::Studio::EventDescription* eventD;
	FMOD::Studio::EventInstance* eventInstance;
	FMOD::Studio::EventInstance* getInstance();

	FMOD_RESULT result;


public:
	Audio(const char* file);

	~Audio();

};

