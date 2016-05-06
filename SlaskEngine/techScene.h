#pragma once
#include "include/Slask.h"

#include "techPlayer.h"
#include "techEnemy.h"
#include "techTestObject.h"
#include "techTestBG.h"

class World:public Scene
{
private:
	Tag menuTag,gameTag;
	Camera cam;
	Player *player;
public:
	World();
	~World();
};

