#pragma once
#include "GraphicsHandler.h"
#include "SteamHandler.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "AudioHandler.h"
#include "LogHandler.h"
#include "File.h"
#include "Input.h"
#include "Font.h"
#include "Audio.h"
#include "AudioBank.h"
#include "Sprite.h"
#include "ListHandle.h"
#include "Timer.h"
#include "SpriteSet.h"
#include "AudioSet.h"
#include "FontSet.h"
#include "Platform.h"
#include "Tag.h"
#include "Camera.h"
#include "DepthItem.h"
#include "Object.h"
#include "Scene.h"
#include "Animation.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

#define _SLASK_BUILDNAME "SlaskEngine"
#define _SLASK_BUILDRELEASE "BETA"
#define _SLASK_BUILDVERSION "100"

class SlaskEngine
{
private:
	//no nonpointers
	SlaskEngine();
	//game loop is active
	bool running;
	//object list
	ListHandle<Object> objects;
	//sprite set list
	std::vector<SpriteSet*> spritesets;
	//audio set list
	std::vector<AudioSet*> audiosets;
	//font set list
	std::vector<FontSet*> fontsets;
	//static instance
	static SlaskEngine *slaskengine;
	//game start function
	static void(*gameStartFunc)();
	//game end function
	static void(*gameEndFunc)();
	//game window resize function
	static void(*gameWindowResizeFunc)();
	//game window close function
	static void(*gameCloseFunc)();
	//queue of newly added objects
	std::vector<Object*> depthQueue;
	//queue of objects changing depth
	std::vector<Object*> depthChangeQueue;
	//list of active tags in beginTag
	std::vector<Tag*> activeTags;
	//entry point of linked depth item list
	DepthItem *firstDepth;
	//current scene
	Scene *scene;
	//whether scenes are switching on the current scene
	bool switchingScenes;
	//calculated passed game time per frame
	double frameTime,frameSeconds;
	//fps calculation, should match graphics handler
	int fps;
	//currently iterated object in frame
	Object *handleObj;
	//for checking if handleObj committed "delete this" so lists can fix themselves
	bool handleObjDeleted;

public:
	//setting the game start function in namespace
	static void setGameStartFunc(void(*func)());
	//setting the game end function in namespace
	static void setGameEndFunc(void(*func)());
	//setting the game window resize function in namespace
	static void setGameWindowResizeFunc(void(*func)());
	//setting the game window close function in namespace
	static void setGameCloseFunc(void(*func)());
	//getting the dynamic instance

	inline static SlaskEngine* instance()
	{
		return slaskengine;
	}

	//scene's request scene change in constructor
	void switchScene(Scene *scn);
	//objects request adding to object listing in constructor
	void createObject(Object *o);
	//sprite sets request adding to listing in constructor
	SpriteSet* createSpriteSet(SpriteSet *ss);
	//audio sets request adding to listing in constructor
	AudioSet* createAudioSet(AudioSet *ss);
	//font sets request adding to listing in constructor
	FontSet* createFontSet(FontSet *ss);
	//get sprite set by index in namespace
	SpriteSet* spriteSet(unsigned int i);
	//get audio set by index in namespace
	AudioSet* audioSet(unsigned int i);
	//get font set by index in namespace
	FontSet* fontSet(unsigned int i);

	//terminate run cycle in namespace or in init running
	inline void gameEnd()
	{
		running = false;
	}

	//sync tag and object in object class
	void objAddTag(Object* o, Tag* );
	//sync tag and object in object class
	void objRemoveTag(Object* o, Tag* t);
	//detach tag and object in tag destructor
	void objUnlinkTag(Object* o, Tag* t);
	//detach tag and object in object destructor
	inline void objClearTag(Object *o, Tag* t)
	{
		t->detachObj(o);
	}
	//tag requests updating object's state
	inline void refreshObjTagDraws(Object *o, bool value)
	{
		o->_refreshTagDraws(value);
	}
	//tag requests updating object's state
	inline void refreshObjTagRuns(Object *o, bool value)
	{
		o->_refreshTagRuns(value);
	}
	//add tag to active tag list in namespace
	void beginTag(Tag *t);
	//remove tag from active tag list in namespace
	void endTag(Tag *t);

	//resolve new depth queue before drawing
	void resolveDepthQueue();
	//resolve depth change queue before drawing
	void resolveDepthChangeQueue();

	//object requests getting added to new depth list in constructor
	void queueDepth(Object *o);
	//object requests getting added to depth change queue
	void queueDepthChange(Object *o);

	//object requests getting added to depth change list
	void detachDepth(Object *o);
	//add a depth to the listing when resolving new depth queue
	void attachDepth(Object *o);
	//depth item requests being the head when it realizes it moved to the top or from the top
	inline void setFirstDepth(DepthItem *d)
	{
		firstDepth = d;
	}

	//release scene at the end of the enging
	inline void deleteScene()
	{
		if (scene)
		{
			scene->_deathMark = 1;
			scene->_deleted=1;
			delete scene;
			scene = NULL;
		}
	}
	//release data sets at the end of the engine
	void deleteAllSets();
	//release object data at the end of the engine
	void deleteAllObjects();

	//check for deletion of currently iterated object in object destructor
	inline void checkDeletedObject(Object* o)
	{
		if (o == handleObj)
		handleObjDeleted = 1;
	}
	//check if the object was illegally deleted during iteration
	inline bool isObjectDestroyed(Object* o)
	{
		return o->_getDestroyed();
	}

	//get the current scene in namespace
	inline Scene* getCurrentScene()
	{
		return scene;
	}

	//retie the object to the current scene in object
	inline void tieObjectToScene(Scene *scn, Object *obj)
	{
		scn->_objects.push_back(obj);
	}
	//untie the object from the current scene in object
	inline void untieObjectFromScene(Scene *scn, Object *obj)
	{
		std::vector<Object*>::const_iterator it = std::find(scn->_objects.begin(), scn->_objects.end(), obj);
		scn->_objects.erase(it);
	}
	//force objects as persistent to detach them from the scene to avoid loops in scene destructor
	inline void forcePersistent(Object *obj)
	{
		obj->_scene = NULL;
		obj->_persistent = 1;
	}

	//get frame seconds in namespace
	inline double getFrameSeconds()
	{
		return frameSeconds;
	}
	//get frame time multiplier in namespace
	inline double getFrameMultiplier()
	{
		return frameTime;
	}
	//set the fps in namespace (graphics handler sync)
	inline void setFPS(int framesps)
	{
		fps = framesps;
	}
	//initialize and run
	void init(int argc, char *argv[]);
	//new
	SlaskEngine(int argc, char *argv[]);
	~SlaskEngine();

	//check if the scene is exiting in object
	inline bool sceneExiting(Scene *scn)
	{
		return (scn&&scn->_getDeleted());
	}

	//debug
	#ifdef SLASKDEBUG
	void dumpObjects();
	void dumpDepths();
	void dumpDepthQueue();
	void dumpDepthChangeQueue();
	void dumpObj(Object *obj);
	#endif
};

#include "Object.h"
#include "Scene.h"
