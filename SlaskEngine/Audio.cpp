#include "Audio.h"
#include "AudioHandler.h"
#include <iostream>


Audio::Audio(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	std::string s = "event:/";
	s += file;

	eventD = NULL;
	result = system->getEvent(s.c_str(), &eventD);
	if (result != FMOD_OK)
		std::cout << "Getting event: " << FMOD_ErrorString(result) << '\n';

	eventInstance = NULL;
	result = eventD->createInstance(&eventInstance);
	if (result != FMOD_OK)
		std::cout << "Creating instance: " << FMOD_ErrorString(result) << '\n';
}

FMOD::Studio::EventInstance* Audio::getInstance()
{
	return eventInstance;
}

Audio::~Audio()
{
	
}