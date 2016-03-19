#include "InputHandler.h"

InputHandler::InputHandler()
{
	key = new int[Keyboard::Key::KeyCount];
	mouse_y = mouse_x = mousewheel_up = mousewheel_down = 0;
	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		mouse_butt[i] = 0;
	}
	for (int i = 0; i < Keyboard::Key::KeyCount; i++)
	{
		key[i] = 0;
	}
}

bool InputHandler::run(RenderWindow* window)
{
	bool close = false;
	Event event;

	for (int i = 0; i < Keyboard::Key::KeyCount; i++)
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
		case Event::Closed:
			close = true;
			break;
		case Event::Resized:
			break;
		case Event::LostFocus:
			break;
		case Event::GainedFocus:
			break;
		case Event::TextEntered:
			break;
		case Event::KeyPressed:
			if (key[event.key.code] == 0)
				key[event.key.code] = 1;
			break;
		case Event::KeyReleased:
			key[event.key.code] = 0;
			break;
		case Event::MouseWheelMoved:
			if (event.mouseWheel.delta < 0)
				mousewheel_down = -event.mouseWheel.delta;
			else
				mousewheel_up = event.mouseWheel.delta;

			mouse_x = event.mouseWheel.x;
			mouse_y = event.mouseWheel.y;
			break;
		case Event::MouseButtonPressed:
			if (event.mouseButton.button < MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 1;
				mouse_x = event.mouseButton.x;
				mouse_y = event.mouseButton.y;
			}
			break;
		case Event::MouseButtonReleased:
			if (event.mouseButton.button < MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 0;
				mouse_x = event.mouseButton.x;
				mouse_y = event.mouseButton.y;
			}
			break;
		case Event::MouseMoved:
			mouse_x = event.mouseMove.x;
			mouse_y = event.mouseMove.y;
			break;
		case Event::MouseEntered:
			break;
		case Event::MouseLeft:
			break;
		case Event::JoystickButtonPressed:
			break;
		case Event::JoystickButtonReleased:
			break;
		case Event::JoystickMoved:
			break;
		case Event::JoystickConnected:
			break;
		case Event::JoystickDisconnected:
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