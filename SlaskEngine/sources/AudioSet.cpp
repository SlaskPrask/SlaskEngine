#include "../include/AudioSet.h"
#include "../include/SlaskEngine.h"


AudioSet::AudioSet()
{
	loads = 0;
	engine_id = -1;
	_deathMark = 0;
	bank = NULL;
	bankFile = "";
	SlaskEngine::instance()->createAudioSet(this);
}


AudioSet::~AudioSet()
{
	if (!_deathMark)
		LogHandler::error("Engine", "delete called on an audio set. Do not delete sets manually.");

	switch (loads)
	{
	case 0:
		break;
	default:
		LogHandler::notify("Resources", "An Audio set was left unloaded before deletion.");
		loads = 1;
		//fallthrough
	case 1:
		unload();
		break;
	}
}

unsigned int AudioSet::id()
{
	return engine_id;
}

void AudioSet::load()
{
	if (bankFile=="")
	{
		LogHandler::notify("Resources", "Attempting to load audio set without a bank.");
		return;
	}
	
	switch (loads)
	{
	case 0:
		//TODO: multithreading
		bank = new AudioBank(bankFile.c_str());

		for (unsigned int i = 0; i < data.size(); i++)
			if (file[i].length()>0)
				data[i] = new Audio(file[i].c_str());
			else
				data[i] = NULL;
		loads = 1;
		break;
	default:
		loads++;
		break;
	}
}

void AudioSet::unload()
{
	switch (loads)
	{
	case 0:
		LogHandler::notify("Resources", "Attempting to unload an already unloaded audio set.");
		break;
	case 1:
		for (unsigned int i = 0; i<data.size(); i++)
		{
			Audio *a = data[i];
			if (a)
			{
				data[i] = NULL;
				delete a;
			}
		}
		delete bank;
		bank = NULL;

		loads = 0;
		break;
	default:
		loads--;
		break;
	}
}

bool AudioSet::isLoaded()
{
	return loads>0;
}

int AudioSet::instances()
{
	return loads;
}

unsigned int AudioSet::add(std::string str) //Make sure the bank path is in slot 0
{
	data.push_back(NULL);
	file.push_back(str);
	return file.size() - 1;
}

void AudioSet::setBank(const char* bank)
{
	bankFile = bank;
}

AudioBank* AudioSet::getBank()
{
	return bank;
}

Audio* AudioSet::get(unsigned int i)
{
	if (i<0 || i >= file.size())
	{
		LogHandler::notify("Resources", "Attempting to access data outside an audio set's range.");
		return NULL;
	}
	else
	{
		if (loads == 0)
		{
			LogHandler::notify("Resources", "Accessing an unloaded audio set.");
			return NULL;
		}		
		return data[i];
	}
}