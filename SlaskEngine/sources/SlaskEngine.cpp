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

	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init("SlaskEngine");

	SteamHandler* steam = SteamHandler::instance();
	steam->init();

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);

	std::string eVer = "Initialized SlaskEngine Version: ";
	eVer += fullEngineVersion;

	LogHandler::log("Engine", eVer.c_str());
	LogHandler::log("-------------------------------------");
	slask::start();//game initialization point

	while (running)
	{
		//input
		if (input->run())
			slask::end();

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

		//audio
		audio->run();
	}
	LogHandler::log("-------------------------------------");
	LogHandler::log("Engine", "Stopped");

	graphics->close();
}

void SlaskEngine::createObject(Object *o)
{
	objects.add(o);
}

void SlaskEngine::gameEnd()
{
	running = false;
}

SlaskEngine::~SlaskEngine()
{
	LogHandler::log("Engine", "End");
}