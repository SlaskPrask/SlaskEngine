#include "../include/SlaskEngine.h"
#include <iostream>
#include "../include/slasknamespace.h"
#include "../include/Object.h"
#include "../include/Scene.h"

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

	Camera *cam;
	running = true;
	firstDepth = NULL;
	scene = NULL;
	switchingScenes = 0;
	frameTime = frameSeconds = 0;
	fps = _SLASK_DEFAULT_FPS;
	handleObjDeleted = 0;

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

	std::ostringstream version;
	version << _SLASK_BUILDNAME << " Version " << _SLASK_BUILDRELEASE << _SLASK_BUILDVERSION <<
	#ifdef WINDOWS
		"-WIN";
	#endif
	#ifdef LINUX
		"-LNX";
	#endif
	#ifdef MAC
		"-MAC";
	#else
		"";
	#endif

	LogHandler::log("Engine", "Initialized");
	LogHandler::log("Engine", version.str().c_str());
	LogHandler::log("-------------------------------------");
	if (gameStartFunc)
	gameStartFunc();//game initialization point
	else
	{
		LogHandler::notify("Engine","No game entry point given.");
		running = false;
	}
	int first=1;/////////////////////////////////////////////////////////////
	graphics->earlyCameraRefresh();

	bool exitHandle=0;
	sf::Clock frameClock;
	double passedMs=0;
	LinkedList<Object> *objI, *nextObjI;
	DepthItem *di,*diNext;
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
				str << "Window resized to " << graphics->getWindow()->getSize().x << "," << graphics->getWindow()->getSize().y;
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

		if (slask::getKeyPress(slask::Key::A))
		{
			dumpObjects();
			dumpDepths();
			dumpDepthQueue();
			dumpDepthChangeQueue();
		}
		if (slask::getKeyPress(slask::Key::B))
		{
			objI = objects.first();
			while (objI)
			{
				nextObjI = objI->getNext();
				((Object*)objI)->depth(((Object*)objI)->depth()+1);
				objI = nextObjI;
			}
			first=1;
		}

		//running
		switchingScenes = 0;
		if (scene)
		scene->run();

		objI = objects.first();
		while (objI)
		{
			handleObj = (Object*)objI;
			handleObjDeleted = 0;
			nextObjI = objI->getNext();
			if (!switchingScenes&&handleObj->isRunEnabled())
				handleObj->run();
			
			if (!handleObjDeleted&&handleObj->_getDestroyed())
			{
				handleObj->_deathMark = 1;
				delete handleObj;
			}

			objI = nextObjI;
		}

		//camera bounds
		cam = graphics->getCamera();
		if (cam)
			cam->doFollow();

		//drawing
		if (first)
		{
			dumpObjects();
			dumpDepths();
			dumpDepthQueue();
			dumpDepthChangeQueue();
		}
		resolveDepthQueue();
		if (first)
		{
			dumpObjects();
			dumpDepths();
			dumpDepthQueue();
			dumpDepthChangeQueue();
		}
		resolveDepthChangeQueue();
		if (first)
		{
			dumpObjects();
			dumpDepths();
			dumpDepthQueue();
			dumpDepthChangeQueue();
		}
		graphics->drawBegin();
		if (di = firstDepth)
		while (di)
		{
			diNext = di->getNext();
			handleObj = di->get();
			handleObjDeleted = 0;
			if (handleObj->isDrawEnabled()&&handleObj->visible&&!handleObj->_getDestroyed()&&!handleObjDeleted)
				handleObj->draw();
			di = diNext;
		}
		graphics->drawEnd();

		//exit handle
		if (exitHandle)
			if (gameEndFunc)
				gameEndFunc();
			else
				gameEnd();

		//fps
		passedMs = (double)frameClock.getElapsedTime().asMicroseconds();
		if (fps > 0)
		{
			sf::sleep(sf::microseconds((sf::Int64)(1000000.0f / fps - passedMs)));
			passedMs = (double)frameClock.getElapsedTime().asMicroseconds();
		}
		frameSeconds=passedMs / 1000000.0f;
		frameTime = frameSeconds*fps;
		frameClock.restart();

		first=0;
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
		str += std::to_string(i);
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
		str += std::to_string(i);
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
		str += std::to_string(i);
		str += "/";
		int size = fontsets.size() - 1;
		str += std::to_string(size);
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
	(new DepthItem(o))->addAbove(firstDepth);
}

void SlaskEngine::switchScene(Scene *scn)
{
	switchingScenes = 1;
	if (scene)
	{
		scene->_deathMark = 1;
		delete scene;
	}
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
		((Object*)obj)->_deathMark = 1;
		delete obj;
		obj = objects.first();
	}
}

void SlaskEngine::deleteAllSets()
{
	for (unsigned int i = 0; i < spritesets.size(); i++)
	{
		spritesets[i]->_deathMark = 1;
		delete spritesets[i];
	}
	spritesets.clear();

	for (unsigned int i = 0; i < audiosets.size(); i++)
	{
		audiosets[i]->_deathMark = 1;
		delete audiosets[i];
	}
	audiosets.clear();

	for (unsigned int i = 0; i < fontsets.size(); i++)
	{
		fontsets[i]->_deathMark = 1;
		delete fontsets[i];
	}
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

#ifdef SLASKDEBUG
void SlaskEngine::dumpObjects()
{
	LogHandler::log("DUMP","OBJECTS:");
	int i=0;
	LinkedList<Object> *obj = objects.first();
	while (obj)
	{
		LinkedList<Object> *nextObj= obj->getNext();
		std::ostringstream s;
		s << std::to_string(i) << ": " << (Object*)obj;
		LogHandler::log("DUMP",s.str().c_str());
		i++;
		obj = nextObj;
	}

	LogHandler::log("DUMP","");
}
void SlaskEngine::dumpDepths()
{
	LogHandler::log("DUMP","DEPTHS:");
	DepthItem *di,*diNext;
	int i=0;
	if (di = firstDepth)
	while (di)
	{
		diNext = di->getNext();
		std::ostringstream s;
		s << std::to_string(i) << ": ";
		
		if (di->getPrevious())
		s << di->getPrevious() << "(" << di->getPrevious()->get() << ":" << di->getPrevious()->getDepth() << ") -> ";
		else
		s << ((Object*)NULL) << "(" << ((Object*)NULL) << ":-) -> ";

		s << di << "(" << di->get() << ":" << di->getDepth() << ")";
		
		if (di->getNext())
		s << " -> " << di->getNext() << "(" << di->getNext()->get() << ":" << di->getNext()->getDepth() << ")";
		else
		s << " -> " << ((Object*)NULL) << "(" << ((Object*)NULL) << ":-)";
		
		LogHandler::log("DUMP",s.str().c_str());
		i++;

		di = diNext;
	}

	LogHandler::log("DUMP","");
}
void SlaskEngine::dumpDepthQueue()
{
	LogHandler::log("DUMP","DEPTH QUEUE:");
	for(unsigned int i=0;i<depthQueue.size();i++)
	{
		std::ostringstream s;
		s << std::to_string(i) << ": " << depthQueue[i] << " " << depthQueue[i]->_depth << "->" << depthQueue[i]->_qdepth;
		LogHandler::log("DUMP",s.str().c_str());
		depthQueue[i];
	}

	LogHandler::log("DUMP","");
}
void SlaskEngine::dumpDepthChangeQueue()
{
	LogHandler::log("DUMP","DEPTH CHANGE QUEUE:");
	for (unsigned int i=0;i<depthChangeQueue.size();i++)
	{
		std::ostringstream s;
		s << std::to_string(i) << ": " << depthChangeQueue[i] << " " << depthChangeQueue[i]->_depth << "->" << depthChangeQueue[i]->_qdepth;
		LogHandler::log("DUMP",s.str().c_str());
		depthChangeQueue[i];
	}

	LogHandler::log("DUMP","");
}
void SlaskEngine::dumpObj(Object *obj)
{
	std::ostringstream s;
	s << "OBJECT: " << obj;
	LogHandler::log("DUMP",s.str().c_str());
	s.str("");
	s << "DEPTH OBJ: " << obj->_depthItem;
	LogHandler::log("DUMP",s.str().c_str());
	s.str("");
	s << "DEPTH: " << std::to_string(obj->_depth) << "->" << std::to_string(obj->_qdepth);
	LogHandler::log("DUMP",s.str().c_str());
	s.str("");
	s << "X,Y: " << std::to_string(obj->x) << "," << std::to_string(obj->y);
	LogHandler::log("DUMP",s.str().c_str());
	s.str("");
	s << (obj->visible?"VISIBLE":"INVISIBLE");
	LogHandler::log("DUMP",s.str().c_str());

	LogHandler::log("DUMP","");
}
#endif
