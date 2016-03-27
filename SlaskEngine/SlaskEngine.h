#pragma once
#include "GraphicsHandler.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "AudioHandler.h"
#include "slasknamespace.h"
#include "LogHandler.h"
#include "FileHandler.h"
#include <cmath>

class SlaskEngine
{
private:
	bool running;

public:
	static SlaskEngine* instance();

	void init();
	SlaskEngine();
	~SlaskEngine();
};

