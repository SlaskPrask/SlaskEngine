#pragma once
#include <SFML/System.hpp>
#include <SFML/Window/Touch.hpp>
#include "GraphicsHandler.h"
#include "LogHandler.h"

#define _SLASK_MAXMOUSEBUTTONS (5)
#define _SLASK_MAXJOYSTICKS (8)

class InputHandler
{
private:
	int mouse_x, mouse_y;
	double mouse_cam_prev_x, mouse_cam_prev_y;
	double mouse_cam_x, mouse_cam_y;
	double mouse_cam_moved_x, mouse_cam_moved_y;
	int mouse_butt[_SLASK_MAXMOUSEBUTTONS];
	bool mouse_ignore[_SLASK_MAXMOUSEBUTTONS];
	bool mouse_clear[_SLASK_MAXMOUSEBUTTONS];
	bool *key_clear, anykeyclear;
	int mousewheel_up,mousewheel_down;
	bool mousewheelup_clear,mousewheeldown_clear;
	int anykeycount;
	double deadzone[_SLASK_MAXJOYSTICKS];
	double buttondeadzone[_SLASK_MAXJOYSTICKS];

	std::string keyboardstr;

	int *key;
	bool anykeyreleased,anykeypressed;
	int anykeyheld;

	bool signal_resize;
	bool signal_focus;
	bool window_focus;

	bool touchTranslation;
	int touchClick;
	bool touchNoPosition;
	int touchNoPositionX,touchNoPositionY;

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

	inline void setTouchTranslation(bool enabled)
	{
		touchTranslation = enabled;
	}

	void addKeyboardChar(std::string *s, bool newlines = 0);

	void clearmouse(int i);
	bool clearedmouse(int i);
	void clearkey(int i);
	bool clearedkey(int i);
	inline bool clearedkeyany()
	{
		return anykeyclear;
	}
	inline bool clearkeyany()
	{
		anykeyclear = 1;
	}

	inline void setNoTouchPosition(int x, int y)
	{
		touchNoPosition = 1;
		touchNoPositionX = x;
		touchNoPositionY = y;
	}

	inline void unsetNoTouchPosition()
	{
		touchNoPosition = 0;
		touchNoPositionX = -1;
		touchNoPositionY = -1;
	}

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