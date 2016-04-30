#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"
#include "techEnemy.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	SpriteSet *marioSprites = new SpriteSet();//id 0
	marioSprites->add("slask.png");//id 0
	SpriteSet *enemySprites = new SpriteSet();//id 1
	enemySprites->add("slask.png");//id 0 and this would ofc be some other png

	AudioSet *stringsAudio = new AudioSet();
	stringsAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	AudioSet *masterAudio = new AudioSet();
	masterAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.bank");
	masterAudio->add("Music");
	masterAudio->add("Audio");

	FontSet *basicFont = new FontSet();
	basicFont->add("Propagandae.otf");

	//should be done in scene
	marioSprites->load();
	enemySprites->load();

	stringsAudio->load();
	masterAudio->load();

	TestObject *bgObj = new TestObject;
	bgObj->taggy = new Tag();
	bgObj->taggy2 = new Tag();
	(new player())->at(getWindowWidth()/2,getWindowHeight()/2);
	for (int i = 0; i < 30; i++)
	{
		techEnemy *enemy = new techEnemy();
		enemy->addTag(bgObj->taggy);
		if ((i / 2) * 2 == i)//every other also has taggy2
		enemy->addTag(bgObj->taggy2);
	}
	//
}

void slask::end()
{
	log("WindowCLosed");

	//should be done in scene
	spriteSet(0)->unload();//mario sprites
	spriteSet(1)->unload();//enemy sprites
	audioSet(1)->unload();//master
	audioSet(0)->unload();//strings last
	//fontSet(0)->unload();
	//

	exitGame();
}
