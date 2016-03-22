#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine* SlaskEngine::instance()
{
	static SlaskEngine slaskengine;
	return &slaskengine;
}

SlaskEngine::SlaskEngine() 
{
	init();
}

void SlaskEngine::init()
{
	running = true;
	
	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init(1280, 720, "SlaskEngine");

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);
	Sprite testS("slask.png");
	Audio testA("fmod\TestBank\Build\Desktop\Master Bank.bank");








	while (running)
	{
		if (input->run())
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		/*&FMOD::Studio::System::update;
		FMOD::Studio::EventDescription* spoop = 0;
		audio->getSystem()->getEvent("event:/Audio", &spoop);
		spoop->loadSampleData();
		FMOD::Studio::EventInstance* eventInstance = 0;
		spoop->createInstance(&eventInstance);
		eventInstance->start();
		eventInstance->release();*/


		graphics->drawBegin();
		graphics->drawSprite(&testS, 0, 0, 100, 100);
		graphics->drawEnd();
		
	}
	
	graphics->close();
	
	&FMOD::Studio::Bank::unloadSampleData;

}
SlaskEngine::~SlaskEngine(){
}