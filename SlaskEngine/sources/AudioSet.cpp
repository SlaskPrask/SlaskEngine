#include "AudioSet.h"



AudioSet::AudioSet()
{
	loads = 0;
	engine_id = -1;
}


AudioSet::~AudioSet()
{
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
	switch (loads)
	{
	case 0:
		//TODO: multithreading
		bank = new AudioBank(file[0].c_str());

		for (unsigned int i = 1; i < data.size() + 1; i++)
				data[i-1] = new Audio(file[i].c_str());
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
		delete bank;

		for (unsigned int i = 0; i<data.size(); i++)
		{
			Audio *a = data[i];
			data[i] = NULL;
			delete a;
		}
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
			LogHandler::notify("Resources", "Accessing an unloaded audio set.");
		return data[i];
	}
}