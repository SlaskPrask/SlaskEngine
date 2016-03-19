#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine::SlaskEngine()
{
	running = false;
	
	GraphicsHandler graphics(1280, 720, "SlaskEngine");
	InputHandler input;

	CircleShape shape(100.f);
	shape.setFillColor(Color::Blue);

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