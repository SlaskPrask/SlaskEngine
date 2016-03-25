#include "AudioBank.h"
#include "AudioHandler.h"
#include <iostream>


AudioBank::AudioBank(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	result = system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), &bank);
	if (result != FMOD_OK)
		std::cout << "Loading bank: " << FMOD_ErrorString(result) << '\n';
}

AudioBank::~AudioBank()
{
	bank->unload();
}
