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
	bool mouse_clear[_SLASK_MAXMOUSEBUTTONS];
	int mousewheel_up,mousewheel_down;
	bool mousewheelup_clear,mousewheeldown_clear;
	int anykeycount;
	double deadzone[_SLASK_MAXJOYSTICKS];
	double buttondeadzone[_SLASK_MAXJOYSTICKS];

	int* key;
	bool anykeyreleased,anykeypressed;
	int anykeyheld;

	bool signal_resize;
	bool signal_focus;
	bool window_focus;

	void mousePosition(int mx, int my);

	InputHandler() {}

public:
	inline static InputHandler* instance()
	{
		static InputHandler inputhandler;
		return &inputhandler;
	}

	void init();
	~InputHandler();

	bool run();

	void clearmouse(int i);
	bool clearedmouse(int i);

	inline void clearmousewheel_up()
	{
		mousewheelup_clear = 1;
	}
	inline bool clearedmousewheel_up()
	{
		return mousewheelup_clear;
	}
	inline void clearmousewheel_down()
	{
		mousewheeldown_clear = 1;
	}
	inline bool clearedmousewheel_down()
	{
		return mousewheeldown_clear;
	}

	int getkey(int i);
	int getmouse(int i);
	bool getanykey(int state);
	inline int getmouse_x()
	{
		return mouse_x;
	}
	inline int getmouse_y()
	{
		return mouse_y;
	}
	inline double getmouse_camera_x()
	{
		return mouse_cam_x;
	}
	inline double getmouse_camera_y()
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