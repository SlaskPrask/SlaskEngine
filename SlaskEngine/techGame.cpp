#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"
#include "techEnemy.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	SpriteSet *marioSprites = createSpriteSet();//id 0
	marioSprites->add("slask.png");//id 0
	SpriteSet *enemySprites = createSpriteSet();//id 1
	enemySprites->add("slask.png");//id 0 and this would ofc be some other png

	AudioSet *stringsAudio = createAudioSet();
	stringsAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	AudioSet *masterAudio = createAudioSet();
	masterAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.bank");
	masterAudio->add("Music");
	masterAudio->add("Audio");

	FontSet *basicFont = createFontSet();
	basicFont->add("Propagandae.otf");

	//should be done in scene
	marioSprites->load();
	enemySprites->load();

	stringsAudio->load();
	masterAudio->load();

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
	audioSet(1)->unload();//master
	audioSet(0)->unload();//strings last
	//fontSet(0)->unload();
	//

	exitGame();
}
