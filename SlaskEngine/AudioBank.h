#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

class AudioHandler;

class AudioBank
{
private:
	FMOD::Studio::Bank* bank;
	FMOD::Studio::System* system;

	bool sampleasync;
	bool sampledecompress;
	FMOD_RESULT result;


public:
	AudioBank(const char* file);
	~AudioBank();
};

