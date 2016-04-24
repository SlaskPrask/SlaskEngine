#include "InputHandler.h"

InputHandler* InputHandler::instance()
{
	static InputHandler inputhandler;
	return &inputhandler;
}

void InputHandler::init()
{
	LogHandler::log("Input", "Start");

	key = new int[sf::Keyboard::Key::KeyCount];
	mouse_y = mouse_x = mousewheel_up = mousewheel_down = 0;
	window_focus = true;
	signal_focus = signal_resize = 0;
	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		mouse_butt[i] = 0;
	}
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		key[i] = 0;
	}

	LogHandler::log("Input", "Initialized");
}

bool InputHandler::run()
{
	sf::RenderWindow *window = GraphicsHandler::instance()->getWindow();
	bool close = false;
	sf::Event event;
	
	//0 is not pressed, 1 is initial press, 2 is held down, -1 is initial release
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		if (key[i] == 1)
			key[i] = 2;

		else if (key[i] == -1)
			key[i] = 0;
	}

	for (int i = 0; i < MAXMOUSEBUTTONS; i++)
	{
		if (mouse_butt[i] == 1)
			mouse_butt[i] = 2;
	}

	mousewheel_up = mousewheel_down = 0;

	if (window)
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
			signal_resize = true;
			break;
		case sf::Event::LostFocus:
			window_focus = false;
			signal_focus = true;
			break;
		case sf::Event::GainedFocus:
			window_focus = true;
			signal_focus = true;
			break;
		case sf::Event::TextEntered:
			break;
		case sf::Event::KeyPressed:
			if (event.key.code>=0&&event.key.code<sf::Keyboard::Key::KeyCount)
			if (key[event.key.code] <= 0)
				key[event.key.code] = 1;
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code<sf::Keyboard::Key::KeyCount)
			if (key[event.key.code] > 0)
				key[event.key.code] = -1;
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
			if (event.mouseButton.button>=0 && event.mouseButton.button < MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 1;
				mouse_x = event.mouseButton.x;
				mouse_y = event.mouseButton.y;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button >= 0 && event.mouseButton.button < MAXMOUSEBUTTONS)
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
	if (i>=0&&i<sf::Keyboard::Key::KeyCount)
	return key[i];
	else
	{
		std::string unhandledKey = "Reading key ";
		unhandledKey += i;
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
}

int InputHandler::getmouse(int i)
{
	if (i >= 0 && i<MAXMOUSEBUTTONS)
		return mouse_butt[i];
	else
	{
		std::string unhandledKey = "Reading mouse button ";
		unhandledKey += i;
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
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
	LogHandler::log("Input", "End");
}

bool InputHandler::getSignalResize()
{
	if (signal_resize)
	{
		signal_resize = 0;
		return 1;
	}
	else
	return 0;
}

bool InputHandler::getFocus()
{
	return window_focus;
}

bool InputHandler::getSignalFocus()
{
	if (signal_focus)
	{
		signal_focus = 0;
		return 1;
	}
	else
		return 0;
}

bool InputHandler::getKeyPress(int keyCode)
{
	return key[keyCode] == 1;
}

bool InputHandler::getKeyRelease(int keyCode)
{
	return key[keyCode] == -1;
}

bool InputHandler::getKeyHeld(int keyCode)
{
	return key[keyCode] > 0;
}

bool InputHandler::getKeyIdle(int keyCode)
{
	return key[keyCode] <= 0;
}