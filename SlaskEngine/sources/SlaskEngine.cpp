#include "../include/SlaskEngine.h"
#include <iostream>
#include "../include/slasknamespace.h"

SlaskEngine *SlaskEngine::slaskengine;
void (*SlaskEngine::gameEndFunc)() = NULL;
void(*SlaskEngine::gameStartFunc)() = NULL;
void(*SlaskEngine::gameWindowResizeFunc)() = NULL;

SlaskEngine::SlaskEngine(int argc, char *argv[])
{
	init(argc,argv);
}

void SlaskEngine::setGameStartFunc(void (*func)())
{
	SlaskEngine::gameStartFunc = func;
}

void SlaskEngine::setGameEndFunc(void(*func)())
{
	SlaskEngine::gameEndFunc = func;
}

void SlaskEngine::setGameWindowResizeFunc(void(*func)())
{
	SlaskEngine::gameWindowResizeFunc = func;
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

	Camera *cam;
	running = true;
	firstDepth = NULL;
	scene = NULL;
	switchingScenes = 0;

	srand((unsigned int)time(NULL));

	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init("Game");

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
	#ifdef WINDOWS
	eVer += "-WIN";
	#endif
	#ifdef LINUX
	eVer += "-LNX";
	#endif
	#ifdef MAC
	eVer += "-MAC";
	#endif

	LogHandler::log("Engine", eVer.c_str());
	LogHandler::log("-------------------------------------");
	if (gameStartFunc)
	gameStartFunc();//game initialization point
	else
	{
		LogHandler::notify("Engine","No game entry point given.");
		running = false;
	}
	graphics->earlyCameraRefresh();

	bool exitHandle=0;

	while (running)
	{
		//audio
		audio->run();

		//input
		exitHandle = input->run();

		if (input->getSignalResize())
		{
			if (graphics->getWindow())
			{
				std::ostringstream str;
				str << "Window resized to " << graphics->getWindow()->getSize().x << "," << graphics->getWindow()->getSize().x;
				LogHandler::log("Engine", str.str().c_str());
			}
			else
			{
				LogHandler::log("Engine", "Window resized, unknown window");
			}
			graphics->resize();
			if (gameWindowResizeFunc)
				gameWindowResizeFunc();
		}

		//running
		switchingScenes = 0;
		LinkedList<Object> *obj = objects.first();
		while (obj)
		{
			if (!switchingScenes&&((Object*)obj)->_tagRuns())
				((Object*)obj)->run();
			if (((Object*)obj)->_getDestroyed())
			{
				if (objects.last() == obj)
				{
					delete obj;
					break;
				}
				else
				{
					LinkedList<Object> *obj2 = obj;
					obj = obj->getNext();
					delete obj2;
				}
			}
			else
				obj = obj->getNext();
		}

		//camera bounds
		cam = graphics->getCamera();
		if (cam)
			cam->doFollow();

		//drawing
		resolveDepthQueue();
		resolveDepthChangeQueue();
		graphics->drawBegin();
		if (firstDepth)
		{
			DepthItem *di = firstDepth;
			Object *obj;
			while (di)
			{
				obj = di->get();
				if (obj->_tagDraws()&&!obj->_getDestroyed())
				{
					obj->draw();
				}
				di = di->getNext();
			}
		}
		graphics->drawEnd();

		//exit handle
		if (exitHandle)
			if (gameEndFunc)
				gameEndFunc();
			else
				gameEnd();
	}
	LogHandler::log("Engine", "Stopping..");
	deleteScene();
	deleteAllObjects();
	deleteAllSets();
	LogHandler::log("-------------------------------------");
	LogHandler::log("Engine", "Stopped");

	graphics->close();
}

void SlaskEngine::createObject(Object *o)
{
	objects.add(o);
	//active tags
	for (std::vector<Tag*>::iterator it = activeTags.begin(); it != activeTags.end(); ++it)
		o->addTag(*it);

	if (scene)
	{
		o->_persistent = 0;
		o->_scene = scene;
		tieObjectToScene(scene, o);
	}
}


SpriteSet* SlaskEngine::createSpriteSet(SpriteSet *ss)
{
	ss->engine_id = spritesets.size();
	spritesets.push_back(ss);
	return ss;
}

AudioSet* SlaskEngine::createAudioSet(AudioSet *ss)
{
	ss->engine_id = audiosets.size();
	audiosets.push_back(ss);
	return ss;
}

FontSet* SlaskEngine::createFontSet(FontSet *ss)
{
	ss->engine_id = fontsets.size();
	fontsets.push_back(ss);
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
		LogHandler::error("Engine", str.c_str());
		return NULL;
	}
	return spritesets[i];
}

AudioSet* SlaskEngine::audioSet(unsigned int i)
{
	if (i < 0 || i >= audiosets.size())
	{
		std::string str = "Attempting to access audio set ";
		str += i;
		str += "/";
		int size = audiosets.size() - 1;
		str += size;
		str += " out of range. (Starting from 0.)";
		LogHandler::error("Engine", str.c_str());
		return NULL;
	}
	return audiosets[i];
}

FontSet* SlaskEngine::fontSet(unsigned int i)
{
	if (i < 0 || i >= fontsets.size())
	{
		std::string str = "Attempting to access font set ";
		str += i;
		str += "/";
		int size = fontsets.size() - 1;
		str += size;
		str += " out of range. (Starting from 0.)";
		LogHandler::error("Engine", str.c_str());
		return NULL;
	}
	return fontsets[i];
}

void SlaskEngine::resolveDepthQueue()
{
	while (depthQueue.size())
	{
		attachDepth(depthQueue.back()->_copyDepth());
		depthQueue.pop_back();
	}
}

void SlaskEngine::queueDepth(Object *o)
{
	std::vector<Object*>::const_iterator it = std::find(depthQueue.begin(), depthQueue.end(), o);
	if (it == depthQueue.end())
	{
		depthQueue.push_back(o);
	}
}

void SlaskEngine::resolveDepthChangeQueue()
{
	while (depthChangeQueue.size())
	{
		depthChangeQueue.back()->_performDepthMove();
		depthChangeQueue.pop_back();
	}
}

void SlaskEngine::queueDepthChange(Object *o)
{
	std::vector<Object*>::const_iterator it = std::find(depthChangeQueue.begin(), depthChangeQueue.end(), o);
	if (it == depthChangeQueue.end())
	{
		depthChangeQueue.push_back(o);
	}
}

void SlaskEngine::detachDepth(Object *o)
{
	for (std::vector<Object*>::iterator it = depthQueue.begin(); it != depthQueue.end(); ++it)
	if (o == (*it))
	{
		depthQueue.erase(it);
		return;
	}

	if (o->_depthItem == firstDepth)
		firstDepth = o->_depthItem->getNext();
	delete (o->_depthItem);
}

void SlaskEngine::attachDepth(Object *o)
{
	if (!firstDepth)
	firstDepth = new DepthItem(o);
	else
	firstDepth->addBelow(new DepthItem(o));
}

void SlaskEngine::switchScene(Scene *scn)
{
	switchingScenes = 1;
	if (scene)
		delete scene;
	scene = scn;
}

void SlaskEngine::beginTag(Tag *t) 
{
	std::vector<Tag*>::const_iterator it = std::find(activeTags.begin(), activeTags.end(), t);
	if (it == activeTags.end())
		activeTags.push_back(t);
	else
		LogHandler::notify("Engine","Function beginTag() called twice on the same tag.");
}
void SlaskEngine::endTag(Tag *t)
{
	std::vector<Tag*>::const_iterator it = std::find(activeTags.begin(), activeTags.end(), t);
	if (it == activeTags.end())
		LogHandler::notify("Engine", "Function endTag() called on a tag that is not active.");
	else
		activeTags.erase(it);
}

void SlaskEngine::deleteAllObjects()
{
	LinkedList<Object> *obj = objects.first();
	while (obj)
	{
		delete obj;
		obj = objects.first();
	}
}

void SlaskEngine::deleteAllSets()
{
	for (unsigned int i = 0; i < spritesets.size(); i++)
		delete spritesets[i];
	spritesets.clear();

	for (unsigned int i = 0; i < audiosets.size(); i++)
		delete audiosets[i];
	audiosets.clear();

	for (unsigned int i = 0; i < fontsets.size(); i++)
		delete fontsets[i];
	fontsets.clear();
}

void SlaskEngine::objAddTag(Object* o, Tag* t)
{
	if (t->attachObj(o))
	{
		o->_tags.push_back(t);
		o->_refreshTagRuns(t->runs());
		o->_refreshTagDraws(t->draws());
	}
}

void SlaskEngine::objRemoveTag(Object* o, Tag* t)
{
	if (t->detachObj(o))
	{
		std::vector<Tag*>::const_iterator it = std::find(o->_tags.begin(), o->_tags.end(), t);
		o->_tags.erase(it);
		o->_refreshTagRuns(1);
		o->_refreshTagDraws(1);
	}
}

void SlaskEngine::objUnlinkTag(Object* o, Tag* t)
{
	std::vector<Tag*>::const_iterator it = std::find(o->_tags.begin(), o->_tags.end(), t);
	o->_tags.erase(it);
	o->_refreshTagRuns(1);
	o->_refreshTagDraws(1);
}

SlaskEngine::~SlaskEngine()
{
	LogHandler::log("Engine", "End");
}
