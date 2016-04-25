#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	SpriteSet *marioSprites = createSpriteSet(new SpriteSet());//id 0
	marioSprites->add("slask.png");//id 0

	SpriteSet *enemySprites = createSpriteSet(new SpriteSet());//id 1
	enemySprites->add("slask.png");//id 0

	marioSprites->load();

	createObject(new TestObject());
	createObject(new player());
}

void slask::end()
{
	log("WindowCLosed");

	spriteSet(0)->unload();//mario sprites
	spriteSet(1)->unload();//enemy sprites
	exitGame();
}
