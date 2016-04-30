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

public:
	static SlaskEngine* instance();

	void createObject(Object *o);
	SpriteSet* createSpriteSet(SpriteSet *ss);
	AudioSet* createAudioSet(AudioSet *ss);
	FontSet* createFontSet(FontSet *ss);
	SpriteSet* spriteSet(unsigned int i);
	AudioSet* audioSet(unsigned int i);
	FontSet* fontSet(unsigned int i);
	void gameEnd();
	void deleteAllObjects();
	void objAddTag(Object* o, Tag* t, std::vector<Tag*>* tagv);
	void objRemoveTag(Object* o, Tag* t, std::vector<Tag*>* tagv);
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

	void deleteAllSets();

	void init(int argc, char *argv[]);
	SlaskEngine(int argc, char *argv[]);
	~SlaskEngine();
};
