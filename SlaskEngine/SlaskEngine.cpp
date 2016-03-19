#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine::SlaskEngine()
{
	RenderWindow window(VideoMode(1280, 720), "I'M SLASK"/*, Style::Titlebar*/);
	window.setFramerateLimit(60);

	InputHandler input;
	CircleShape shape(100.f);
	shape.setFillColor(Color::Blue);

	while (window.isOpen())
	{
		if(input.run(&window))
			window.close();

		cout << input.getkey(InputHandler::Pause) << endl;

		window.clear();
		window.draw(shape);
		window.display();
	}
}
SlaskEngine::~SlaskEngine(){}