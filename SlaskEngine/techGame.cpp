#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"
#include "techEnemy.h"
#include "techTestBG.h"

using namespace slask;

void techGameStart()
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
	basicFont->add("Progandae.otf");

	//should be done in scene
	marioSprites->load();
	enemySprites->load();

	stringsAudio->load();
	masterAudio->load();

	basicFont->load();

	testBG *bgObj = new testBG();
	Tag *tag1 = new Tag();
	Tag *tag2 = new Tag();
	(new player())->at(getWindowWidth()/2,getWindowHeight()/2);
	for (int i = 0; i < 30; i++)
	{
		techEnemy *enemy = new techEnemy();
		enemy->addTag(tag1);
		if ((i / 2) * 2 == i)//every other also has taggy2
		enemy->addTag(tag2);
	}
	TestObject *testObj = new TestObject;
	testObj->taggy = tag1;
	testObj->taggy2 = tag2;
	//
}

void techGameEnd()
{
	log("Window closed");

	//should be done in scene
	spriteSet(0)->unload();//mario sprites
	spriteSet(1)->unload();//enemy sprites
	audioSet(1)->unload();//master
	audioSet(0)->unload();//strings last
	fontSet(0)->unload();//font
	//

	exitGame();
}
