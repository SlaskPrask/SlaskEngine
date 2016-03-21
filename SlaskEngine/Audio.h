#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>
#include "AudioHandler.h"

class Audio
{
private:
	FMOD::Studio::Bank** bank;
	FMOD::Studio::System* system;
	bool sampleasync;
	bool sampledecompress;

public:
	Audio(const char* file);
	~Audio();

};

