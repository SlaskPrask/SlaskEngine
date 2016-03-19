#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine::SlaskEngine()
{
	running = true;
	
	GraphicsHandler graphics(1280, 720, "SlaskEngine");
	InputHandler input;

	while (running)
	{
		if (input.run(graphics.getWindow()))
			running = false;

		//cout << input.getkey(InputHandler::Pause) << endl;

		graphics.drawBegin();
		graphics.drawEnd();
	}
	graphics.close();
}
SlaskEngine::~SlaskEngine(){}