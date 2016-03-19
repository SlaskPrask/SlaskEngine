#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine::SlaskEngine()
{
	running = true;
	RenderWindow window(VideoMode(1280, 720), "I'M SLASK"/*, Style::Titlebar*/);
	window.setFramerateLimit(60);

	GraphicsHandler graphics(1280, 720, "SlaskEngine");
	InputHandler input;

	CircleShape shape(100.f);
	shape.setFillColor(Color::Blue);

	while (running)
	{
		if (input.run(graphics.getWindow()))
			window.close();

		//cout << input.getkey(InputHandler::Pause) << endl;

		window.clear();
		window.draw(shape);
		window.display();
	}
}
SlaskEngine::~SlaskEngine(){}