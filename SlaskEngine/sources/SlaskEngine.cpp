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
	LogHandler::setFile("log.txt");
	LogHandler::log("Engine", "Start");
	
	
	engineBuild = "ALPHA";
	engineVersion = 1.0f;
	fullEngineVersion = engineBuild;
	fullEngineVersion += std::to_string(engineVersion);

	running = true;

	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init("SlaskEngine");

	SteamHandler* steam = SteamHandler::instance();
	steam->init();

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);

	std::string eVer = "Initialized SlaskEngine Version: ";
	eVer += fullEngineVersion;

	LogHandler::log("Engine", eVer.c_str());
	LogHandler::log("-------------------------------------");
	slask::start();//game initialization point


	//this is temp stuff just for testing
	Timer timer;
	File file;
	
	timer.startTimer();
	Sprite testS("slask.png");
	Font testF("Progandae.otf");
	AudioBank TestMB("fmod/TestBank/Build/Desktop/Master Bank.bank");
	AudioBank TestMSB("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	Audio Team10("Music");
	Audio Guitar("Audio");
	int position = 0;
	
	file.add("Hi");
	file.add("Zas");
	file.add(19123);
	file.add("I'm Slask");
	file.save("Save Test.txt", true);

	file.load("Save Test.txt", true);
	file.set(1, "Slask");
	file.set(2, 12);
	std::cout << file.get(0) << '\n';
	std::cout << file.get(1) << '\n';
	std::cout << file.getint(2) << '\n';
	std::cout << file.get(3) << '\n';

	file.searchFile(&files, "Saves/", "*.txt");
	//file.compare(&files, "TestCompare.txt");

	file.deleteSave(5, "Saves/", "SAVE", "txt", "Slask");
	file.deleteSave(3, "Saves/", "SAVE", "txt", "Zas");
	file.checkSaves(&files, 5, "Saves/", "SAVE", "txt");
	file.newSave(3, "Saves/", "SAVE", "txt", "Zas");
	file.copySave(2, 5, "Saves/", "SAVE", "txt", "Slask");

	std::cout << std::to_string(timer.getTime()).c_str() << std::endl;
	//end of temp

	while (running)
	{
		if (input->run())
			running = false;
		if (input->getSignalResize())
		{
			LogHandler::log("Engine", "Window resized.");
			graphics->resize();
		}

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


			if (input->getkey(slask::Key::LShift) && input->getkey(slask::Key::Z) == 1)
			{
				graphics->setFullscreenWindowed(1920,1080);
			}
			if (input->getkey(slask::Key::LShift) && input->getkey(slask::Key::X) == 1)
			{
				graphics->setWindowed(1280,720);
			}
			if (input->getkey(slask::Key::LShift) && input->getkey(slask::Key::C) == 1)
			{
				graphics->setWindowed(800,600);
			}
			if (input->getkey(slask::Key::LShift) && input->getkey(slask::Key::V)==1)
			{
				graphics->setFullscreen(1920,1080);
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
	LogHandler::log("-------------------------------------");
	LogHandler::log("Engine", "Stopped");

	graphics->close();
}

SlaskEngine::~SlaskEngine()
{
	LogHandler::log("Engine", "End");
}