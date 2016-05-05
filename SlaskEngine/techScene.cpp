#include "techScene.h"

using namespace slask;

World::World()
{
	width = 1000;
	height = 600;

	spriteSet(0)->load();
	fontSet(0)->load();

	new testBG();
	new TestObject();
	player=at(new Player(), width / 2, height / 2);
	for (int i = 0; i < 30; i++)
	{
		at(new techEnemy(), random(width), random(height));
	}

	cam.setSize(1280/2,720/2);
	cam.setBounds(120,100);
	cam.setLimits(width,height);
	cam.follow(player);
	cam.setPositionCentered(player);
	cam.activate();


}

World::~World()
{
	spriteSet(0)->unload();
	fontSet(0)->unload();
}
