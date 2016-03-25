#include "Audio.h"
#include <iostream>


Audio::Audio(const char* file)
{
	std::string s = "event:/";
	s += file;

	std::cout << s.c_str() << '\n';

	eventD = NULL;
	result = system->getEvent(s.c_str(), &eventD);
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