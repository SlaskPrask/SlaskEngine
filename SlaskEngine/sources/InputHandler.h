#pragma once
#include <SFML/System.hpp>
#include "GraphicsHandler.h"
#include "LogHandler.h"

#define MAXMOUSEBUTTONS (5)
#define MAXJOYSTICKS (8)

class InputHandler
{
private:
	int mouse_x, mouse_y;
	double mouse_cam_x,mouse_cam_y;
	int mouse_butt[MAXMOUSEBUTTONS];
	int mousewheel_up;
	int mousewheel_down;
	double deadzone[MAXJOYSTICKS];
	double buttondeadzone[MAXJOYSTICKS];

	int* key;

	bool signal_resize;
	bool signal_focus;
	bool window_focus;

	void mousePosition(int mx, int my);

	InputHandler() {}

public:
	static InputHandler* instance();

	void init();
	~InputHandler();

	bool run();

	int getkey(int i);
	int getmouse(int i);

	inline int getmouse_x()
	{
		return mouse_x;
	}
	inline int getmouse_y()
	{
		return mouse_y;
	}
	inline int getmouse_camera_x()
	{
		return mouse_cam_x;
	}
	inline int getmouse_camera_y()
	{
		return mouse_cam_y;
	}
	inline int getmousewheel_up()
	{
		return mousewheel_up;
	}
	inline int getmousewheel_down()
	{
		return mousewheel_down;
	}

	bool getSignalResize();
	bool getFocus();
	bool getSignalFocus();
};