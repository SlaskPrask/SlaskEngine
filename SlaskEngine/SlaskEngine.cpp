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
	graphics->init(1280,720,"SlaskEngine");

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);
	
	//this is temp stuff just for testing
	Sprite testS("slask.png");
	Font testF("Progandae.otf");
	AudioBank TestMB("fmod/TestBank/Build/Desktop/Master Bank.bank");
	AudioBank TestMSB("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	Audio Team10("Music");
	Audio Guitar("Audio");
	int position = 0;
	


	while (running)
	{
		if (input->run())
			running = false;
		if (input->getSignalResize())
			graphics->resize();

		/*TESTING GAME CODE*/
		{
			position += 3;
			if (position>360)
				position -=360;

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
			//the big at the back, stretched
			graphics->drawSprite(&testS, 10, 10, graphics->getWidth() - 20, graphics->getHeight() - 20, 1000);
			//small not moving, static position
			graphics->drawSprite(&testS, 100, 100, 1);
			//rolling one, static position
			graphics->drawSprite(&testS, 100 + cos(position*3.14159265 / 180.0f) * 100, 100 + sin(position*3.14159265 / 180.0f) * 100, 10);
			//spinning whole, static position
			graphics->drawSpriteRot(&testS, 300, 150, 100, 100, position, -10);
			//spinning red, static position
			graphics->drawSpriteExt(&testS, 150, 400, 200, 100, 0, 0, .5, .5, -position, 1, 0, 0, 0.5, -20);
			//top left, dynamic position
			graphics->drawSpritePoly(&testS, 0, 0, 100, 0, 0, 100, .5, 0, 0, 1, 1, 1, -100);
			//top right, dynamic position
			graphics->drawSpritePoly(&testS, graphics->getWidth(), 0, graphics->getWidth(), 100, graphics->getWidth()-100, 0, .5, 0, 0, 1, 1, 1, -100);
			//bottom left, dynamic position
			graphics->drawSpritePoly(&testS, 0, graphics->getHeight(), 0, graphics->getHeight()-100, 100, graphics->getHeight(), .5, 0, 0, 1, 1, 1, -100);
			//bottom right, dynamic position
			graphics->drawSpritePoly(&testS, graphics->getWidth(), graphics->getHeight(), graphics->getWidth()-100, graphics->getHeight(), graphics->getWidth(), graphics->getHeight()-100, .5, 0, 0, 1, 1, 1, -100);
			//spinning green, static position
			graphics->drawSpritePolyExt(&testS, 300, 200, 200, 400, 400, 400, .5, 0, 0, 1, 1, 1,position*2.0f,0,1,0,1,-100);
		}

		graphics->drawEnd();

		audio->run();
	}

	graphics->close();
}

SlaskEngine::~SlaskEngine()
{
}