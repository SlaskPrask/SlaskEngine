#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>
#include "AudioHandler.h"

class Audio
{
private:
	FMOD::Studio::Bank* bank;
	FMOD::Studio::System* system;

	const char* eventFile;
	bool sampleasync;
	bool sampledecompress;
	FMOD_RESULT result;
	FMOD::Studio::EventDescription* eventD;

public:
	Audio(const char* file);
	void setEvent(const char* file);

	const char* getEvent();

	~Audio();

};

