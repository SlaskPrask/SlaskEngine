#pragma once
#include <SFML/System.hpp>
#include "GraphicsHandler.h"
#include "LogHandler.h"

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

	bool signal_resize;
	bool signal_focus;
	bool window_focus;

	InputHandler() {}

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

	bool getSignalResize();
	bool getFocus();
	bool getSignalFocus();
};