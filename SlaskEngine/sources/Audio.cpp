#include "../include/Audio.h"
#include "../include/AudioHandler.h"


Audio::Audio(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	std::string s = "event:/";
	s += file;

	eventD = NULL;
	eventInstance = NULL;

	result = system->getEvent(s.c_str(), &eventD);
	if (result != FMOD_OK)
	{
		std::string str = "Loading event: ";
		str += FMOD_ErrorString(result);
		LogHandler::error("Audio", str.c_str());
		return;
	}

	result = eventD->createInstance(&eventInstance);
	if (result != FMOD_OK)
	{
		std::string str = "Loading event instance: ";
		str += FMOD_ErrorString(result);
		LogHandler::error("Audio", str.c_str());
		eventInstance = NULL;
		return;
	}
}

FMOD::Studio::EventInstance* Audio::getInstance()
{
	return eventInstance;
}

Audio::~Audio()
{
	if (eventInstance) 
	{
		eventInstance->release();
		//delete eventInstance; //TODO: check if needed (crashes)
		eventInstance = NULL;
	}
	if (eventD)
	{
		//delete eventD; //TODO: check if needed (crashes)
		eventD = NULL;
	}
}
