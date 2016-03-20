#pragma once
#include "GraphicsHandler.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "AudioHandler.h"


class SlaskEngine
{
private:
	bool running;

public:
	static SlaskEngine* instance();

	void init();
	~SlaskEngine();
	
};