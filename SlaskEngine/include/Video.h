#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"

class Video
{
private:

public:
	Video(const char* file);
	~Video();

	void playVideo();
	void registerCodec();
};

