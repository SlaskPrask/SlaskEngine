#pragma once
#include "GraphicsHandler.h"
#include "SteamHandler.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "AudioHandler.h"
#include "slasknamespace.h"
#include "LogHandler.h"
#include "File.h"
#include "Input.h"
#include "Object.h"
#include "Scene.h"
#include "Font.h"
#include "Audio.h"
#include "AudioBank.h"
#include "Sprite.h"
#include "Timer.h"
#include <cmath>

class SlaskEngine
{
private:
	bool running;
	std::vector<std::string> files;
	const char* engineBuild;
	float engineVersion;
	std::string fullEngineVersion;

public:
	static SlaskEngine* instance();

	void init();
	SlaskEngine();
	~SlaskEngine();
};

