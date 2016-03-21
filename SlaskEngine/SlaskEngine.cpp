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
	cout << GraphicsHandler::instance() << "\n";
	cout << GraphicsHandler::instance() << "\n";

	running = true;
	
	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init(1280, 720, "SlaskEngine");

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);
	Sprite test("slask.png");
	


	while (running)
	{
		if (input->run())
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		graphics->drawBegin();
		graphics->drawSprite(&test, 0, 0, 100, 100);
		graphics->drawEnd();
	}
	graphics->close();

}
SlaskEngine::~SlaskEngine(){
}