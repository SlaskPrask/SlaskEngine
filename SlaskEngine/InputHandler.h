#pragma once
#include <SFML/System.hpp>
#include "GraphicsHandler.h"
#define MAXMOUSEBUTTONS (5)

class InputHandler
{
private:
	int mouse_x;
	int mouse_y;
	int mouse_butt[MAXMOUSEBUTTONS];
	int mousewheel_up;
	int mousewheel_down;

	int* key;

public:
	static InputHandler* instance();

	void init();
	~InputHandler();

	bool run();

	int getkey(int i);
	int getmouse(int i);
	int getmousewheel_up();
	int getmousewheel_down();
	int getmouse_x();
	int getmouse_y();
};