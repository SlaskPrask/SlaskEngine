#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine* SlaskEngine::instance()
{
	static SlaskEngine slaskengine;
	return &slaskengine;
}

void SlaskEngine::init()
{
	init();
	cout << GraphicsHandler::instance() << "\n";
	cout << GraphicsHandler::instance() << "\n";

	running = true;
	
	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init(1280, 720, "SlaskEngine");

	InputHandler* input = InputHandler::instance();

	AudioHandler* audio = AudioHandler::instance();

	Sprite test("slask.png");
	


	while (running)
	{
		if (input->run())
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		graphics->drawBegin();
		graphics->drawEnd();
	}
	graphics->close();

}
SlaskEngine::~SlaskEngine(){
}