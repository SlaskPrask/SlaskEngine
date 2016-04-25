#pragma once
#include <vector>
#include "LogHandler.h"
#include "SpriteSet.h"
#include <thread>
#include <mutex>


class Loader
{

private:
	std::mutex mtxloader;
	std::thread threadloader;

	//hopefully doesn't optimize
	std::vector<SpriteSet*> spriteset;
	//std::vector<SoundSet*> soundset;



public:
	Loader();
	~Loader();

	void load(SpriteSet *set);
	//void load(SoundSet *set);
	void acuallyload();
};

