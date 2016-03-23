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
	
	Audio testA("fmod/TestBank/Build/Desktop/Master Bank.bank");
	Audio testB("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	FMOD::Studio::EventInstance* eventInstance = 0;
	FMOD::Studio::EventDescription* spoop = 0;

	cout << spoop << endl;

	while (running)
	{
		if (input->run())
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		&FMOD::Studio::System::update;
		audio->getSystem()->getEvent("event:/Master Bank/Audio", &spoop);
		spoop->loadSampleData();
		spoop->createInstance(&eventInstance);
		eventInstance->start();
		eventInstance->release();


		graphics->drawBegin();
		graphics->drawSprite(&testS, 0, 0, 100, 100);
		graphics->drawEnd();
		
	}
	
	graphics->close();
	
	cout << spoop << endl;

	&FMOD::Studio::Bank::unloadSampleData;

	cout << spoop << endl;

}
SlaskEngine::~SlaskEngine(){
}