#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>

class Video
{
private:

public:
	Video(const char* file);
	~Video();

	void playVideo();
	void registerCodec();
};

