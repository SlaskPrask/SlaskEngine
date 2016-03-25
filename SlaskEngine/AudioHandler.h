#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>
#include "Audio.h"
#include "AudioBank.h"


class AudioHandler
{
private:
	FMOD::Studio::System* audioSys;
	FMOD::System* lowLevelSys;

	int driverCount;
	int maxChannels;
	void setMaxChannels(int channels);
	void *extraDriverData;


	bool sampleasync; 
	bool sampledecompress;

	FMOD_RESULT result;

public:
	static AudioHandler* instance();

	void init(int channels);
	~AudioHandler();

	FMOD_STUDIO_LOAD_BANK_FLAGS getSampleFlags()
	{
		//return FMOD_STUDIO_LOAD_BANK_NORMAL;
		return (FMOD_STUDIO_LOAD_BANK_NONBLOCKING*sampleasync) | (FMOD_STUDIO_LOAD_BANK_DECOMPRESS_SAMPLES*sampledecompress);
	}

	int getMaxChannels();

	void setSampleDecompress(bool enabled);
	void setSampleASync(bool enabled);
	void play();

	//void loadEvent(Audio* audio, const char* event);

	FMOD::Studio::System* getSystem();
};

