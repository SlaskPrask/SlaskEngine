#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine* SlaskEngine::instance()
{
	static SlaskEngine slaskengine;
	return &slaskengine;
}


void SlaskEngine::init() /*SlaskEngine::SlaskEngine()*/
{
	running = true;
	
	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init(1280, 720, "SlaskEngine");

	InputHandler input;
	Sprite test("slask.png");

	while (running)
	{
		if (input.run(graphics->getWindow()))
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		graphics->drawBegin();
		graphics->drawEnd();
	}
	graphics->close();
}
SlaskEngine::~SlaskEngine()
{

}