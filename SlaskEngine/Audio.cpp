#include "Audio.h"



Audio::Audio(const char* file)
{
	FMOD_RESULT 
		FMOD::Studio::System::loadBankFile(file, FMOD_STUDIO_LOAD_BANK_FLAGS flags, bank);

}


Audio::~Audio()
{
}
