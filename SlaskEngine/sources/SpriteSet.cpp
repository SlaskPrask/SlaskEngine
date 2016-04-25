#include "SpriteSet.h"

SpriteSet::SpriteSet()
{
	loads = 0;
	engine_id = -1;
}

SpriteSet::~SpriteSet()
{
	switch (loads)
	{
	case 0:
		break;
	default:
		LogHandler::notify("Resources", "A sprite set was left unloaded before deletion.");
		loads = 1;
		//fallthrough
	case 1:
		unload();
		break;
	}
}

unsigned int SpriteSet::id()
{
	return engine_id;
}

void SpriteSet::load()
{
	switch (loads)
	{
	case 0:
		//TODO: multithreading
		for (unsigned int i = 0; i<data.size(); i++)
			data[i] = new Sprite(file[i].c_str());
		loads = 1;
		break;
	default:
		loads++;
		break;
	}
}

void SpriteSet::unload()
{
	switch (loads)
	{
	case 0:
		LogHandler::notify("Resources", "Attempting to unload an already unloaded sprite set.");
		break;
	case 1:
		for (unsigned int i = 0; i<data.size(); i++)
		{
			Sprite *s = data[i];
			data[i] = NULL;
			delete s;
		}
		loads = 0;
	default:
		loads--;
	}
}

bool SpriteSet::isLoaded()
{
	return loads>0;
}

int SpriteSet::instances()
{
	return loads;
}

unsigned int SpriteSet::add(std::string str)
{
	data.push_back(NULL);
	file.push_back(str);
	return file.size() - 1;
}

Sprite* SpriteSet::get(unsigned int i)
{
	if (i<0 || i >= file.size())
	{
		LogHandler::notify("Resources", "Attempting to access data outside a sprite set's range.");
		return NULL;
	}
	else
	{
		if (loads == 0)
			LogHandler::notify("Resources", "Accessing an unloaded sprite set.");
		return data[i];
	}
}