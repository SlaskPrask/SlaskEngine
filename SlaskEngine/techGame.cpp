#include "include/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"
#include "techEnemy.h"
#include "techTestBG.h"
#include "techScene.h"

using namespace slask;

void techGameStart()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	SpriteSet *marioSprites = new SpriteSet();//id 0
	marioSprites->add("slask.png");//id 0

	AudioSet *stringsAudio = new AudioSet();
	stringsAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	AudioSet *masterAudio = new AudioSet();
	masterAudio->setBank("fmod/TestBank/Build/Desktop/Master Bank.bank");
	masterAudio->add("Music");
	masterAudio->add("Audio");

	FontSet *basicFont = new FontSet();
	basicFont->add("Progandae.otf");

	stringsAudio->load();
	masterAudio->load();

	new World();
}

void techGameEnd()
{
	audioSet(1)->unload();//master
	audioSet(0)->unload();//strings last

	exitGame();
}
