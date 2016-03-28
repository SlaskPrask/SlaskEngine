#pragma once

#define MAXJOYSTICKS (8)

class Input
{

private:
	int joystick;
	int id;
	int type;

public:

	enum InputType { Mouse, Keyboard, JoystickButton, JoystickAxis };
	enum Axis { Normal, Inverted, Half, HalfInverted };
	
Input();
~Input();

void buttonToAxisDeadzone(); 
void axisDeadZone();

double getDeadZone();
void setDeadZone();
void axisType();

int getint();
double get();
};