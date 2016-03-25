#include "SlaskEngine.h"
#include <iostream>

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
	Font testF("Progandae.otf");

	AudioBank TestMB("fmod/TestBank/Build/Desktop/Master Bank.bank");
	AudioBank TestMSB("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	Audio Team10("Music");
	Audio Guitar("Audio");


	while (running)
	{
		if (input->run())
			running = false;
		
		/*TESTING GAME CODE*/
		{
			if (input->getkey(slask::Key::Num1) == 1)
			{
				audio->play(&Team10);
			}
			if (input->getkey(slask::Key::Q) == 1)
			{
				audio->stop(&Team10);
			}
			if (input->getkey(slask::Key::Num2) == 1)
			{
				audio->play(&Guitar);
			}
			if (input->getkey(slask::Key::W) == 1)
			{
				audio->stop(&Guitar);
			}
		}



		graphics->drawBegin();

		/*TESTING DRAWING*/
		{
			graphics->drawSprite(&testS, 0, 0, 100, 100);
		}

		graphics->drawEnd();

		audio->run();
	}

	graphics->close();
}

SlaskEngine::~SlaskEngine()
{
}