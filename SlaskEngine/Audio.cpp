#include "Audio.h"
#include <iostream>


Audio::Audio(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	result = system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), &bank);
	if (result != FMOD_OK)
		std::cout << "Loading bank: " << FMOD_ErrorString(result) << '\n';
}

void Audio::setEvent(const char* file)
{
	eventFile = file;

	result = system->getEvent(eventFile, &eventD);
	if (result != FMOD_OK)
		std::cout << "Getting event: " << FMOD_ErrorString(result) << '\n';
}

const char* Audio::getEvent()
{
	return eventFile;
}


Audio::~Audio()
{
	system->unloadAll();
}