#include "SlaskEngine.h"
#include <iostream>
#include "slasknamespace.h"

SlaskEngine *SlaskEngine::slaskengine;

SlaskEngine* SlaskEngine::instance()
{
	return slaskengine;
}

SlaskEngine::SlaskEngine(int argc, char *argv[])
{
	init(argc,argv);
}

void SlaskEngine::init(int argc, char *argv[])
{
	SlaskEngine::slaskengine = this;

	LogHandler::setFile("log.txt");
	LogHandler::log("Engine", "Start");
	
	engineBuild = "ALPHA";
	engineVersion = 1.0f;
	fullEngineVersion = engineBuild;
	fullEngineVersion += std::to_string(engineVersion);

	running = true;

	srand((unsigned int)time(NULL));

	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init("SlaskEngine");

	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);
	audio->run();

	#ifndef NO_STEAM
	SteamHandler* steam = SteamHandler::instance();
	steam->init();
	#endif

	InputHandler* input = InputHandler::instance();
	input->init();


	std::string eVer = "Initialized SlaskEngine Version: ";
	eVer += fullEngineVersion;

	LogHandler::log("Engine", eVer.c_str());
	LogHandler::log("-------------------------------------");
	slask::start();//game initialization point

	bool exitHandle=0;

	while (running)
	{
		//audio
		audio->run();

		//input
		exitHandle = input->run();

		if (input->getSignalResize())
		{
			LogHandler::log("Engine", "Window resized.");
			graphics->resize();
		}

		//running
		LinkedList<Object> *obj=objects.first();
		while (obj)
		{
			((Object*)obj)->run();
			if (((Object*)obj)->_getDestroyed())
			{
				if (objects.last() == obj)
				break;
				else
				{
					obj = obj->getNext();
					delete (Object*)obj;
				}
			}
			else
			obj = obj->getNext();
		}

		//drawing
		graphics->drawBegin();
		obj = objects.first();
		while (obj)
		{
			((Object*)obj)->draw();
			obj = obj->getNext();
		}
		graphics->drawEnd();

		//exit handle
		if (exitHandle)
		slask::end();
	}
	LogHandler::log("Engine", "Stopping..");
	deleteAllObjects();
	deleteAllSpriteSets();
	LogHandler::log("-------------------------------------");
	LogHandler::log("Engine", "Stopped");

	graphics->close();
}

void SlaskEngine::createObject(Object *o)
{
	objects.add(o);
}

SpriteSet* SlaskEngine::createSpriteSet(SpriteSet *ss)
{
	ss->engine_id = spritesets.size();
	spritesets.push_back(ss);
	return ss;
}

SpriteSet* SlaskEngine::spriteSet(unsigned int i)
{
	if (i < 0 || i >= spritesets.size())
	{
		std::string str = "Attempting to access sprite set ";
		str += i;
		str += "/";
		int size = spritesets.size() - 1;
		str += size;
		str += " out of range. (Starting from 0.)";
		LogHandler::error("File", str.c_str());
		return NULL;
	}
	return spritesets[i];
}

void SlaskEngine::gameEnd()
{
	running = false;
}

void SlaskEngine::deleteAllObjects()
{
	while (objects.first())
	{
		delete (Object*)objects.first();
	}
}

void SlaskEngine::deleteAllSpriteSets()
{
	for (unsigned int i = 0; i < spritesets.size(); i++)
		delete spritesets[i];
	spritesets.clear();
}


SlaskEngine::~SlaskEngine()
{
	LogHandler::log("Engine", "End");
}