#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"
#include "techEnemy.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	SpriteSet *marioSprites = createSpriteSet(new SpriteSet());//id 0
	marioSprites->add("slask.png");//id 0

	SpriteSet *enemySprites = createSpriteSet(new SpriteSet());//id 1
	enemySprites->add("slask.png");//id 0

	//should be done in scene
	marioSprites->load();
	enemySprites->load();

	createObject(new TestObject());
	createObject(new player())->at(getWindowWidth()/2,getWindowHeight()/2);
	for (int i = 0; i < 30; i++)
	createObject(new techEnemy());
	//
}

void slask::end()
{
	log("WindowCLosed");

	//should be done in scene
	spriteSet(0)->unload();//mario sprites
	spriteSet(1)->unload();//enemy sprites
	//

	exitGame();
}
