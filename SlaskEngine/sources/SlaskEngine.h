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
#include <cmath>

class SlaskEngine
{
private:
	SlaskEngine();
	bool running;
	const char* engineBuild;
	float engineVersion;
	std::string fullEngineVersion;
	ListHandle<Object> objects;
	static SlaskEngine *slaskengine;

public:
	static SlaskEngine* instance();

	void createObject(Object *o);
	void gameEnd();

	void init(int argc, char *argv[]);
	SlaskEngine(int argc, char *argv[]);
	~SlaskEngine();
};
