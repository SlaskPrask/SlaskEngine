#include "Audio.h"
#include <iostream>


Audio::Audio(const char* file)
{
	eventD = NULL;
	result = system->getEvent(file, &eventD);
	if (result != FMOD_OK)
		std::cout << "Getting event: " << FMOD_ErrorString(result) << '\n';

	eventInstance = NULL;
	result = eventD->createInstance(&eventInstance);
	if (result != FMOD_OK)
		std::cout << "Creating instance: " << FMOD_ErrorString(result) << '\n';
}

Audio::~Audio()
{
	system->unloadAll();
}