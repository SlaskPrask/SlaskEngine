#pragma once
class Input
{

private:
	int joystick;
	int id;
	int type;

public:
	enum InputType { Mouse, Keyboard, JoystickButton, JoystickAxis };
Input();
~Input();

void buttonToAxisDeadzone(); 
void axisDeadZone();

int getint();
double get();
};

