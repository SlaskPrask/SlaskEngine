#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>
#include "Audio.h"


class AudioHandler
{
private:
	FMOD::Studio::System* audioSys;

	int driverCount;
	int maxChannels;
	void setMaxChannels(int channels);
	void *extraDriverData;

	bool sampleasync; 
	bool sampledecompress;

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

	FMOD::Studio::System* getSystem();
};

