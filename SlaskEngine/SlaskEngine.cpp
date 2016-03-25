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
			if (input->getkey(slask::Key::A) == 1) 
			{
				audio->pause(&Team10);
			}
			if (input->getkey(slask::Key::Z) == 1)
			{
				audio->unpause(&Team10);
			}
			if (input->getkey(slask::Key::Num2) == 1)
			{
				audio->play(&Guitar);
			}
			if (input->getkey(slask::Key::W) == 1)
			{
				audio->stop(&Guitar);
			}
			if (input->getkey(slask::Key::S) == 1)
			{
				audio->pause(&Guitar);
			}
			if (input->getkey(slask::Key::X) == 1)
			{
				audio->unpause(&Guitar);
			}
			if (input->getkey(slask::Key::Num3) == 1)
			{
				audio->setPitch(&Guitar, 2);
				audio->setPitch(&Team10, 2);
			}
			if (input->getkey(slask::Key::Num4) == 1)
			{
				audio->setPitch(&Guitar, 0.5f);
				audio->setPitch(&Team10, 0.5f);
			}
			if (input->getkey(slask::Key::Num5) == 1)
			{
				audio->setPitch(&Guitar, 1);
				audio->setPitch(&Team10, 1);
			}
			if (input->getkey(slask::Key::Num0) == 1)
			{
				//OH YEAH
				audio->setTimePosition(&Team10, 37678);
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