#include "InputHandler.h"

InputHandler* InputHandler::instance()
{
	static InputHandler inputhandler;
	return &inputhandler;
}

void InputHandler::init()
{
	key = new int[sf::Keyboard::Key::KeyCount];
	mouse_y = mouse_x = mousewheel_up = mousewheel_down = 0;
	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		mouse_butt[i] = 0;
	}
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		key[i] = 0;
	}
}

bool InputHandler::run()
{
	sf::RenderWindow *window = GraphicsHandler::instance()->getWindow();
	bool close = false;
	sf::Event event;
	
	//0 is not pressed, 1 is initial press, 2 is held down
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		if (key[i] == 1)
			key[i] = 2;
	}

	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		if (mouse_butt[i] == 1)
			mouse_butt[i] = 2;
	}

	mousewheel_up = mousewheel_down = 0;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		default:
			break;
		case sf::Event::Closed:
			close = true;
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::LostFocus:
			break;
		case sf::Event::GainedFocus:
			break;
		case sf::Event::TextEntered:
			break;
		case sf::Event::KeyPressed:
			if (key[event.key.code] == 0)
				key[event.key.code] = 1;
			break;
		case sf::Event::KeyReleased:
			key[event.key.code] = 0;
			break;
		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta < 0)
				mousewheel_down = -event.mouseWheel.delta;
			else
				mousewheel_up = event.mouseWheel.delta;

			mouse_x = event.mouseWheel.x;
			mouse_y = event.mouseWheel.y;
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button < MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 1;
				mouse_x = event.mouseButton.x;
				mouse_y = event.mouseButton.y;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button < MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 0;
				mouse_x = event.mouseButton.x;
				mouse_y = event.mouseButton.y;
			}
			break;
		case sf::Event::MouseMoved:
			mouse_x = event.mouseMove.x;
			mouse_y = event.mouseMove.y;
			break;
		case sf::Event::MouseEntered:
			break;
		case sf::Event::MouseLeft:
			break;
		case sf::Event::JoystickButtonPressed:
			break;
		case sf::Event::JoystickButtonReleased:
			break;
		case sf::Event::JoystickMoved:
			break;
		case sf::Event::JoystickConnected:
			break;
		case sf::Event::JoystickDisconnected:
			break;
		}
	}
	return close;
}

int InputHandler::getkey(int i)
{
	return key[i];
}

int InputHandler::getmouse(int i)
{
	return mouse_butt[i];
}

int InputHandler::getmouse_x()
{
	return mouse_x;
}

int InputHandler::getmouse_y()
{
	return mouse_y;
}

int InputHandler::getmousewheel_up()
{
	return mousewheel_up;
}

int InputHandler::getmousewheel_down()
{
	return mousewheel_down;
}

InputHandler::~InputHandler()
{
	delete key;
}