#pragma once
#include <fmod_errors.h>
#include <fmod_studio.hpp>

class Audio
{
private:
	
	FMOD::Studio::Bank* bank;

public:
	Audio(const char* file);
	~Audio();
};

