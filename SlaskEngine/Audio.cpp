#include "Audio.h"



Audio::Audio(const char* file)
{
	system = AudioHandler::instance()->getSystem();
	system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), bank);
}



Audio::~Audio()
{
	system = AudioHandler::instance()->getSystem();
	system->unloadAll();
}