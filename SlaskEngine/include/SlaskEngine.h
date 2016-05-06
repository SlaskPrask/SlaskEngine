#pragma once
#include "GraphicsHandler.h"
#include "SteamHandler.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "AudioHandler.h"
#include "LogHandler.h"
#include "File.h"
#include "Input.h"
#include "Object.h"
#include "Scene.h"
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
#include <cmath>
#include <ctime>
#include <cstdlib>

class SlaskEngine
{
private:
	SlaskEngine();
	bool running;
	const char* engineBuild;
	float engineVersion;
	std::string fullEngineVersion;
	ListHandle<Object> objects;
	std::vector<SpriteSet*> spritesets;
	std::vector<AudioSet*> audiosets;
	std::vector<FontSet*> fontsets;
	static SlaskEngine *slaskengine;
	static void(*gameStartFunc)();
	static void(*gameEndFunc)();
	static void(*gameWindowResizeFunc)();
	std::vector<Object*> depthQueue;
	std::vector<Object*> depthChangeQueue;
	std::vector<Tag*> activeTags;//begin tag,end tag
	DepthItem *firstDepth;
	Scene *scene;
	bool switchingScenes;

public:
	static void setGameStartFunc(void(*func)());
	static void setGameEndFunc(void(*func)());
	static void setGameWindowResizeFunc(void(*func)());
	inline static SlaskEngine* instance()
	{
		return slaskengine;
	}

	void switchScene(Scene *scn);

	void createObject(Object *o);
	SpriteSet* createSpriteSet(SpriteSet *ss);
	AudioSet* createAudioSet(AudioSet *ss);
	FontSet* createFontSet(FontSet *ss);
	SpriteSet* spriteSet(unsigned int i);
	AudioSet* audioSet(unsigned int i);
	FontSet* fontSet(unsigned int i);
	inline void gameEnd()
	{
		running = false;
	}
	void objAddTag(Object* o, Tag* );
	void objRemoveTag(Object* o, Tag* t);
	void objUnlinkTag(Object* o, Tag* t);
	inline void objClearTag(Object *o, Tag* t)
	{
		t->detachObj(o);
	}
	inline void refreshObjTagDraws(Object *o, bool value)
	{
		o->_refreshTagDraws(value);
	}
	inline void refreshObjTagRuns(Object *o, bool value)
	{
		o->_refreshTagRuns(value);
	}
	void queueDepth(Object *o);
	void detachDepth(Object *o);
	void attachDepth(Object *o);
	inline void setFirstDepth(DepthItem *d)
	{
		firstDepth = d;
	}
	void resolveDepthQueue();

	void beginTag(Tag *t);
	void endTag(Tag *t);

	void resolveDepthChangeQueue();
	void queueDepthChange(Object *o);

	inline void deleteScene()
	{
		if (scene)
		{
			delete scene;
			scene = NULL;
		}
	}
	void deleteAllSets();
	void deleteAllObjects();

	inline Scene* getCurrentScene()
	{
		return scene;
	}
	inline void tieObjectToScene(Scene *scn, Object *obj)
	{
		scn->_objects.push_back(obj);
	}

	inline void untieObjectFromScene(Scene *scn, Object *obj)
	{
		std::vector<Object*>::const_iterator it = std::find(scn->_objects.begin(), scn->_objects.end(), obj);
		scn->_objects.erase(it);
	}

	void init(int argc, char *argv[]);
	SlaskEngine(int argc, char *argv[]);
	~SlaskEngine();
};
