#include "Audio.h"



Audio::Audio(const char* file, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
{
	system->loadBankFile(file, flags, bank);
}

void Audio::setSampleDecompress(bool enabled)
{
	sampledecompress = enabled;
}
void Audio::setSampleASync(bool enabled)
{
	sampleasync = enabled;
}

Audio::~Audio()
{
	system->unloadAll();
}