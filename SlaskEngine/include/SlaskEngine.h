#pragma once
#include "../include/GraphicsHandler.h"
#include "../include/SteamHandler.h"
#include "../include/InputHandler.h"
#include "../include/Sprite.h"
#include "../include/AudioHandler.h"
#include "../include/LogHandler.h"
#include "../include/File.h"
#include "../include/Input.h"
#include "../include/Object.h"
#include "../include/Scene.h"
#include "../include/Font.h"
#include "../include/Audio.h"
#include "../include/AudioBank.h"
#include "../include/Sprite.h"
#include "../include/ListHandle.h"
#include "../include/Timer.h"
#include "../include/SpriteSet.h"
#include "../include/AudioSet.h"
#include "../include/FontSet.h"
#include "../include/Platform.h"
#include "../include/Tag.h"
#include "../include/Camera.h"
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
	static void (*gameStartFunc)();
	static void (*gameEndFunc)();

public:
	static void setGameStartFunc(void(*func)());
	static void setGameEndFunc(void(*func)());
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

	void deleteAllSets();

	void init(int argc, char *argv[]);
	SlaskEngine(int argc, char *argv[]);
	~SlaskEngine();
};
