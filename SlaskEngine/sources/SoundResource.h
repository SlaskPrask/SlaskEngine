#include <vector>
#include "AudioBank.h"
#include "AudioBus.h"
#include "Audio.h"

#pragma once
class SoundResource
{
private:
	typedef std::vector<Audio*> AudioVector;
	AudioVector audio;

	typedef std::vector<AudioBank*> AudioBankVector;
	AudioBankVector audioBank;

	typedef std::vector<AudioBus*> AudioBusVector;
	AudioBusVector audioBus;


public:
	SoundResource();
	~SoundResource();
};

