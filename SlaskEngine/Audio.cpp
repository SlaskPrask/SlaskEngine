#include "Audio.h"
#include <iostream>


Audio::Audio(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	result = system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), &bank);
	if (result != FMOD_OK)
		std::cout << "Loading bank: " << FMOD_ErrorString(result) << '\n';
}

Audio::~Audio()
{
	system->unloadAll();
}