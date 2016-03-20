#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

class Audio
{
private:
	
	FMOD::Studio::Bank** bank;
	bool sampleasync;
	bool sampledecompress;

public:
	Audio(const char* file, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	~Audio();

	FMOD_STUDIO_LOAD_BANK_FLAGS getSampleFlags()
	{
		return (FMOD_STUDIO_LOAD_BANK_NONBLOCKING*sampleasync) | (FMOD_STUDIO_LOAD_BANK_DECOMPRESS_SAMPLES*sampledecompress);
	}

	void setSampleDecompress(bool enabled);
	void setSampleASync(bool enabled);
};

