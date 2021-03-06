#include "../include/InputHandler.h"

void InputHandler::init()
{
	LogHandler::log("Input", "Start");

	key = new int[sf::Keyboard::Key::KeyCount];
	key_clear = new bool[sf::Keyboard::Key::KeyCount];
	anykeyclear = 0;
	mouse_y = mouse_x = mousewheel_up = mousewheel_down = 0;
	mouse_cam_y = mouse_cam_x = mouse_cam_moved_x = mouse_cam_moved_y = mouse_cam_prev_x = mouse_cam_prev_y = 0;
	window_focus = 1;
	keyboardstr = "";
	touchClick = 0;
	touchTranslation = 0;
	touchNoPosition = 0;
	touchNoPositionX = -1;
	touchNoPositionY = -1;
	signal_focus = signal_resize = 0;
	anykeyreleased = anykeypressed = 0;
	anykeyheld = 0;
	for (int i = 0; i < _SLASK_MAXMOUSEBUTTONS; i++)
	{
		mouse_butt[i] = 0;
		mouse_clear[i] = 0;
		mouse_ignore[i] = 0;
	}
	mousewheelup_clear=mousewheeldown_clear = 0;
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		key[i] = 0;
		key_clear[i] = 0;
	}

	for (int i = 0; i < _SLASK_MAXJOYSTICKS; i++)
	{
		for (int j = 0; j < _SLASK_MAXJOYBUTTONS; j++)
		{
			joy_butt[i][j] = 0;
			joy_clear[i][j] = 0;
		}
	}

	LogHandler::log("Input", "Initialized");
}

bool InputHandler::run()
{
	sf::RenderWindow *window = GraphicsHandler::instance()->getWindow();
	bool close = false;
	sf::Event event;
	
	if (touchTranslation)
		switch (touchClick)
		{
		case 1:
			if (mouse_butt[0] <= 0)
				touchClick = -1;
			else
				touchClick = 2;
			break;
		case -1:
			touchClick = 0;
			//TODO: issue with clicking again on this frame?
			break;
		case 2:
			if (mouse_butt[0] <= 0)
				touchClick = -1;
			break;
		default:
			break;
		}

	//0 is not pressed, 1 is initial press, 2 is held down, -1 is initial release
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		if (key[i] == 1)
			key[i] = 2;
		else
		if (key[i] == -1)
			key[i] = 0;
		key_clear[i] = 0;
	}

	for (int i = 0; i < _SLASK_MAXMOUSEBUTTONS; i++)
	{
		if (mouse_butt[i] == 1)
			mouse_butt[i] = 2;
		else 
		if (mouse_butt[i] == -1)
			mouse_butt[i] = 0;
		mouse_clear[i] = 0;
	}

	for (int i = 0; i < _SLASK_MAXJOYSTICKS; i++)
	{
		for (int j = 0; j < _SLASK_MAXJOYBUTTONS; j++)
		{
			if (joy_butt[i][j] == 1)
				joy_butt[i][j] = 2;
			else
				if (joy_butt[i][j] == -1)
					joy_butt[i][j] = 0;
			joy_clear[i][j] = 0;
		}
	}

	anykeyreleased = anykeypressed = 0;
	anykeyclear = 0;

	mousewheel_up = mousewheel_down = 0;
	mousewheelup_clear = mousewheeldown_clear = 0;

	mouse_cam_prev_x = mouse_cam_x;
	mouse_cam_prev_y = mouse_cam_y;

	keyboardstr = "";
	
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
			if (event.text.unicode < 128)
			keyboardstr+=(char)event.text.unicode;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code >= 0 && event.key.code < sf::Keyboard::Key::KeyCount)
				if (key[event.key.code] <= 0)
				{
					key[event.key.code] = 1;
					anykeypressed = 1;
					anykeyheld++;
				}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code<sf::Keyboard::Key::KeyCount)
				if (key[event.key.code] > 0)
				{
					key[event.key.code] = -1;
					anykeyreleased = 1;
					anykeyheld--;
				}
			break;
		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta < 0)
				mousewheel_down = -event.mouseWheel.delta;
			else
				mousewheel_up = event.mouseWheel.delta;

			mousePosition(event.mouseWheel.x, event.mouseWheel.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (touchTranslation&&event.mouseButton.button == 0)
			{
				touchClick = 1;
			}
			if (event.mouseButton.button>=0 && event.mouseButton.button < _SLASK_MAXMOUSEBUTTONS)
			{
				mouse_butt[event.mouseButton.button] = 1;
				mousePosition(event.mouseButton.x, event.mouseButton.y);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button >= 0 && event.mouseButton.button < _SLASK_MAXMOUSEBUTTONS)
			{
				if (mouse_butt[event.mouseButton.button]>0)
				mouse_butt[event.mouseButton.button] = -1;
				mousePosition(event.mouseButton.x, event.mouseButton.y);
			}
			break;
		case sf::Event::MouseMoved:
			mousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseEntered:
			break;
		case sf::Event::MouseLeft:
			break;
		case sf::Event::TouchBegan:
			break;
		case sf::Event::JoystickButtonPressed:
			if (event.joystickButton.button >= 0 && event.joystickButton.button < _SLASK_MAXJOYBUTTONS)
			{
				joy_butt[event.joystickButton.joystickId][event.joystickButton.button] = 1;
			}
			break;
		case sf::Event::JoystickButtonReleased:
			if (event.joystickButton.button >= 0 && event.joystickButton.button < _SLASK_MAXJOYBUTTONS)
			{
				if (joy_butt[event.joystickButton.joystickId][event.joystickButton.button]>0)
					joy_butt[event.joystickButton.joystickId][event.joystickButton.button] = 0;
			}
			break;
		case sf::Event::JoystickMoved:
			joy_axis[event.joystickMove.joystickId][event.joystickMove.axis] = event.joystickMove.position /100.0f;
			break;
		case sf::Event::JoystickConnected:
			break;
		case sf::Event::JoystickDisconnected:
			break;
		}
	}
	
	//ignore presses outside the camera (black bar region)
	if (mouse_cam_x < GraphicsHandler::instance()->getCameraX() ||
		mouse_cam_x >= GraphicsHandler::instance()->getCameraX() + GraphicsHandler::instance()->getCameraW() ||
		mouse_cam_y < GraphicsHandler::instance()->getCameraY() ||
		mouse_cam_y >= GraphicsHandler::instance()->getCameraY() + GraphicsHandler::instance()->getCameraH())
	{
		if (touchClick == 1)
			touchClick = 0;
		for (int i = 0; i < _SLASK_MAXMOUSEBUTTONS; i++)
		{
			if (mouse_butt[i] == 1)
				mouse_butt[i] = 0;
		}
	}

	mouse_cam_moved_x = mouse_cam_x - mouse_cam_prev_x;
	mouse_cam_moved_y = mouse_cam_y - mouse_cam_prev_y;
	if (touchTranslation)
	{
		if (mouse_butt[0] == 1 || touchClick == 1)
		mouse_cam_moved_x = mouse_cam_moved_y = 0;
		if (touchNoPosition&&touchClick == 0)
		mousePosition(touchNoPositionX, touchNoPositionY);
	}

	if (touchClick != 0)
	{
		std::ostringstream s;
		s << mouse_x << "," << mouse_y << " " << mouse_cam_moved_x << "," << mouse_cam_moved_y << " " << touchClick;
		LogHandler::log(s.str().c_str());
	}
	return close;
}

void InputHandler::mousePosition(int mx, int my)
{
	mouse_x = mx;
	mouse_y = my;
	GraphicsHandler *gh = GraphicsHandler::instance();
	if (gh->getCameraW() == gh->getWidth())
		mouse_cam_x = gh->getCameraX() + (double)mouse_x;
	else
		mouse_cam_x = -gh->getHorBar() + gh->getCameraX() + (double)mouse_x / (double)gh->getWidth()*gh->getRegionW();
	if (gh->getCameraH() == gh->getHeight())
		mouse_cam_y = gh->getCameraY() + (double)mouse_y;
	else
		mouse_cam_y = -gh->getVerBar() + gh->getCameraY() + (double)mouse_y / (double)gh->getHeight()*gh->getRegionH();
}

int InputHandler::getkey(int i)
{
	if (i>=0&&i<sf::Keyboard::Key::KeyCount)
	return key[i];
	else
	{
		std::string unhandledKey = "Reading key ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
}

int InputHandler::getbutton(int i, int j)
{
	if (j >=0 && j < _SLASK_MAXJOYBUTTONS)
		return joy_butt[i][j];
	else
	{
		std::string unhandledKey = "Reading button ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
}

double InputHandler::getaxis(int i, int j)
{
	if (j >= 0 && j < _SLASK_MAXJOYAXES)
		return joy_axis[i][j];
	else
	{
		std::string unhandledKey = "Reading axis ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
}

int InputHandler::getmouse(int i)
{
	if (i >= 0 && i < _SLASK_MAXMOUSEBUTTONS)
	{
		if (touchTranslation&&i == 0)
		return touchClick;
		else
		return mouse_butt[i];
	}
	else
	{
		std::string unhandledKey = "Reading mouse button ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
}

bool InputHandler::getanykey(int state)
{
	switch (state)
	{
	default:
		return 0;
	case -1://release
		return anykeyreleased;
	case 0:
		return (anykeyheld == 0);
	case 1:
		return anykeypressed;
	case 2:
		return (anykeyheld > 0);
	}
	return 0;
}

void InputHandler::addKeyboardChar(std::string *s,bool newlines)
{
	for (unsigned int i = 0; i < keyboardstr.size(); i++)
	{
		if (keyboardstr[i] < 32)
			switch (keyboardstr[i])
			{
			default:
				break;
			case '\n'://newline
			case '\r'://carriage return
				if (newlines)
					*s += '\n';
				break;
			case '\b'://backspace
				if (!s->empty())
					*s = s->substr(0, s->size() - 1);
				break;
			}
		else
			switch (keyboardstr[i])
			{
			case 127://delete
				break;
			default:
				*s += keyboardstr[i];
				break;
			}
	}
}

InputHandler::~InputHandler()
{
	delete[] key;
	delete[] key_clear;
	LogHandler::log("Input", "End");
}

void InputHandler::clearjoy(int i, int j)
{
	if (j < 0 || j >= _SLASK_MAXJOYBUTTONS)
	{
		std::string unhandledJoyButt = "Clearing joystick button ";
		unhandledJoyButt += std::to_string(i);
		unhandledJoyButt += " out of range.";
		LogHandler::notify("Input", unhandledJoyButt.c_str());
	}
	joy_clear[i][j] = 1;
}

bool InputHandler::clearedjoy(int i, int j)
{
	if (j < 0 || j >= _SLASK_MAXJOYBUTTONS)
	{
		std::string unhandledJoyButt = "Reading mouse button ";
		unhandledJoyButt += std::to_string(i);
		unhandledJoyButt += " out of range.";
		LogHandler::notify("Input", unhandledJoyButt.c_str());
		return 0;
	}
	return joy_clear[i][j];
}

void InputHandler::clearmouse(int i)
{
	if (i < 0 || i >= _SLASK_MAXMOUSEBUTTONS)
	{
		std::string unhandledKey = "Clearing mouse button ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
	}
	mouse_clear[i] = 1;
}
bool InputHandler::clearedmouse(int i)
{
	if (i < 0 || i >= _SLASK_MAXMOUSEBUTTONS)
	{
		std::string unhandledKey = "Reading mouse button ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
	return mouse_clear[i];
}

void InputHandler::clearkey(int i)
{
	if (i < 0 || i >= sf::Keyboard::Key::KeyCount)
	{
		std::string unhandledKey = "Clearing key ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
	}
	key_clear[i] = 1;
}
bool InputHandler::clearedkey(int i)
{
	if (i < 0 || i >= sf::Keyboard::Key::KeyCount)
	{
		std::string unhandledKey = "Reading key ";
		unhandledKey += std::to_string(i);
		unhandledKey += " out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		return 0;
	}
	return key_clear[i];
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
