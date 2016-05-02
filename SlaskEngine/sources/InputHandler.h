#pragma once
#include <SFML/System.hpp>
#include "GraphicsHandler.h"
#include "LogHandler.h"

#define _SLASK_MAXMOUSEBUTTONS (5)
#define _SLASK_MAXJOYSTICKS (8)

class InputHandler
{
private:
	int mouse_x, mouse_y;
	double mouse_cam_x,mouse_cam_y;
	int mouse_butt[_SLASK_MAXMOUSEBUTTONS];
	int mousewheel_up;
	int mousewheel_down;
	double deadzone[_SLASK_MAXJOYSTICKS];
	double buttondeadzone[_SLASK_MAXJOYSTICKS];

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
		return (int)mouse_x;
	}
	inline int getmouse_y()
	{
		return (int)mouse_y;
	}
	inline int getmouse_camera_x()
	{
		return (int)mouse_cam_x;
	}
	inline int getmouse_camera_y()
	{
		return (int)mouse_cam_y;
	}
	inline int getmousewheel_up()
	{
		return (int)mousewheel_up;
	}
	inline int getmousewheel_down()
	{
		return (int)mousewheel_down;
	}

	bool getSignalResize();
	bool getFocus();
	bool getSignalFocus();
};