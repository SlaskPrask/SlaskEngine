#include "../include/FontSet.h"
#include "../include/SlaskEngine.h"

FontSet::FontSet()
{
	loads = 0;
	engine_id = -1;
	_deathMark = 0;
	SlaskEngine::instance()->createFontSet(this);
}

FontSet::~FontSet()
{
	if (!_deathMark)
		LogHandler::error("Engine", "delete called on a font set. Do not delete sets manually.");

	switch (loads)
	{
	case 0:
		break;
	default:
		LogHandler::notify("Resources", "A font set was left unloaded before deletion.");
		loads = 1;
		//fallthrough
	case 1:
		unload();
		break;
	}
}

unsigned int FontSet::id()
{
	return engine_id;
}

void FontSet::load()
{
	switch (loads)
	{
	case 0:
		//TODO: multithreading
		for (unsigned int i = 0; i<data.size(); i++)
			data[i] = new Font(file[i].c_str());
		loads = 1;
		break;
	default:
		loads++;
		break;
	}
}

void FontSet::unload()
{
	switch (loads)
	{
	case 0:
		LogHandler::notify("Resources", "Attempting to unload an already unloaded font set.");
		break;
	case 1:
		for (unsigned int i = 0; i<data.size(); i++)
		{
			Font *f = data[i];
			data[i] = NULL;
			delete f;
		}
		loads = 0;
		break;
	default:
		loads--;
		break;
	}
}

bool FontSet::isLoaded()
{
	return loads>0;
}

int FontSet::instances()
{
	return loads;
}

unsigned int FontSet::add(std::string str)
{
	data.push_back(NULL);
	file.push_back(str);
	return file.size() - 1;
}

Font* FontSet::get(unsigned int i)
{
	if (i<0 || i >= file.size())
	{
		LogHandler::notify("Resources", "Attempting to access data outside a font set's range.");
		return NULL;
	}
	else
	{
		if (loads == 0)
		{
			LogHandler::notify("Resources", "Accessing an unloaded font set.");
			return NULL;
		}
		return data[i];
	}
}