#include "../include/Input.h"

//Kappa pls check in

Input::Input()
{
}

/*
int Input::getint()
{

}

double Input::get()
{

}

double Input::getDeadZone()#include "../include/Input.h"

Input::Input()
{
	joystick=0;
	id=0;
	type=Uninitialized;
	axis=Normal;
}

int Input::getButton()
{
	switch (type)
	{
	case Uninitialized:
	default:
		return 0;
	case MouseWheel:
		if (id == 0)
			return (InputHandler->instance()->getmousewheel_up() ? 1 : 0);
		else
			return (InputHandler->instance()->getmousewheel_down() ? 1 : 0);
	case Mouse:
		return InputHandler->instance()->getmouse(id);
	case Keyboard:
		return InputHandler->instance()->getkey(id);
	case JoystickButton:
		return InputHandler->instance()->getjoystickbutton(id);
	case JoystickAxis:
		return InputHandler->instance()->getjoystickaxisstate(id);
#error the state thing on inverted,halfinverted,half
	}
}

double Input::getAxis()
{
	switch (type)
	{
	case Uninitialized:
	default:
		return 0;
	case MouseWheel:
		if (id == 0)
			return (InputHandler->instance()->getmousewheel_up() ? 1 : 0);
		else
			return (InputHandler->instance()->getmousewheel_down() ? 1 : 0);
	case Mouse:
		return (InputHandler->instance()->getmouse(id) ? 1 : 0);
	case Keyboard:
		return (InputHandler->instance()->getkey(id) ? 1 : 0);
	case JoystickButton:
		return (InputHandler->instance()->getjoystickbutton(joystick, id) ? 1 : 0);
	case JoystickAxis:
		{
			switch (axis)
			{
			default:
			case Normal:
				return InputHandler->instance()->getjoystickaxis(joystick, id);
			case Inverted:
				return 1.0f-InputHandler->instance()->getjoystickaxis(joystick, id);
			case Half:
				double v = InputHandler->instance()->getjoystickaxis(joystick, id) - 0.5f;
				return (v*2.0f < 0 ? 0 : (v*2.0f>1 ? 1 : v*2.0f));
			case HalfInverted:
				double v = 1.0f-InputHandler->instance()->getjoystickaxis(joystick, id) - 0.5f;
				return (v*2.0f < 0 ? 0 : (v*2.0f>1 ? 1 : v*2.0f));
			}
		}
	}
}

void Input::bindKey(int i)
{
	id = i;
	type = Keyboard;
}

void Input::bindMouse(int i)
{
	id = i;
	type = Mouse;
}

void Input::bindMouseWheelUp()
{
	id = 0;
	type = MouseWheel;
}

void Input::bindMouseWheelDown()
{
	id = 1;
	type = MouseWheel;
}

void Input::bindJoystickButton(int j, int i)
{
	joystick = j;
	id = i;
	type = JoystickButton;
}

void Input::bindJoystickAxis(int j, int i)
{
	joystick = j;
	id = i;
	type = JoystickAxis;
	axis = Normal;
}

void Input::setAxisType(int i)
{
	axis = i;
}

Input::~Input()
{
}

{

}*/

void Input::buttonToAxisDeadzone()
{

}

void Input::axisDeadZone()
{

}



void Input::setDeadZone()
{

}

void Input::axisType()
{

}

Input::~Input()
{
}
/*

#include "../include/Input.h"

Input::Input()
{
joystick=0;
id=0;
type=Uninitialized;
axis=Normal;
}

int Input::getButton()
{
switch (type)
{
case Uninitialized:
default:
return 0;
case MouseWheel:
if (id == 0)
return (InputHandler->instance()->getmousewheel_up() ? 1 : 0);
else
return (InputHandler->instance()->getmousewheel_down() ? 1 : 0);
case Mouse:
return InputHandler->instance()->getmouse(id);
case Keyboard:
return InputHandler->instance()->getkey(id);
case JoystickButton:
return InputHandler->instance()->getjoystickbutton(id);
case JoystickAxis:
return InputHandler->instance()->getjoystickaxisstate(id);
#error the state thing on inverted,halfinverted,half
}
}

double Input::getAxis()
{
switch (type)
{
case Uninitialized:
default:
return 0;
case MouseWheel:
if (id == 0)
return (InputHandler->instance()->getmousewheel_up() ? 1 : 0);
else
return (InputHandler->instance()->getmousewheel_down() ? 1 : 0);
case Mouse:
return (InputHandler->instance()->getmouse(id) ? 1 : 0);
case Keyboard:
return (InputHandler->instance()->getkey(id) ? 1 : 0);
case JoystickButton:
return (InputHandler->instance()->getjoystickbutton(joystick, id) ? 1 : 0);
case JoystickAxis:
{
switch (axis)
{
default:
case Normal:
return InputHandler->instance()->getjoystickaxis(joystick, id);
case Inverted:
return 1.0f-InputHandler->instance()->getjoystickaxis(joystick, id);
case Half:
double v = InputHandler->instance()->getjoystickaxis(joystick, id) - 0.5f;
return (v*2.0f < 0 ? 0 : (v*2.0f>1 ? 1 : v*2.0f));
case HalfInverted:
double v = 1.0f-InputHandler->instance()->getjoystickaxis(joystick, id) - 0.5f;
return (v*2.0f < 0 ? 0 : (v*2.0f>1 ? 1 : v*2.0f));
}
}
}
}

void Input::bindKey(int i)
{
id = i;
type = Keyboard;
}

void Input::bindMouse(int i)
{
id = i;
type = Mouse;
}

void Input::bindMouseWheelUp()
{
id = 0;
type = MouseWheel;
}

void Input::bindMouseWheelDown()
{
id = 1;
type = MouseWheel;
}

void Input::bindJoystickButton(int j, int i)
{
joystick = j;
id = i;
type = JoystickButton;
}

void Input::bindJoystickAxis(int j, int i)
{
joystick = j;
id = i;
type = JoystickAxis;
axis = Normal;
}

void Input::setAxisType(int i)
{
axis = i;
}

Input::~Input()
{
}

*/