#pragma once
#include "SlaskEngine.h"

namespace slask
{
	/*GraphicsHandler* graphics();
	InputHandler* input();
	AudioHandler* audio();
	LogHandler* log();
	SteamHandler* steam();
	File file();*/

	//implement
	void start();
	void end();

	//call
	void createObject(Object *o);
	SpriteSet* createSpriteSet(SpriteSet *ss);//undocced
	SpriteSet* spriteSet(unsigned int i);//undocced
	Sprite* spriteSetSprite(unsigned int i,unsigned int j);//undocced
	inline Sprite* getSprite(unsigned int i, unsigned int j)
	{
		return spriteSetSprite(i,j);
	}
	void deleteAllObjects();//undocced
	void exitGame();

	void setTitle(const char* title);
	void setFPS(int fps);
	void setVSync(bool enabled);

	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWindowWidth();
	int getWindowHeight();

	int getResolutions();
	int getResolutionWidth(int i);
	int getResolutionHeight(int i);
	bool setFullscreen(int w, int h);
	bool setWindowed(int w, int h);
	bool setFullscreenWindowed(int w, int h);

	//draw sprite at position
	void drawSprite(Sprite* sprite, double x, double y, double depth);
	//draw sprite with size
	void drawSprite(Sprite* sprite, double x, double y, double w, double h, double depth);
	//draw a part of a sprite
	void drawSpritePart(Sprite* sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double depth);
	//draw a sprite rotated
	void drawSpriteRot(Sprite* sprite, double x, double y, double w, double h, double rot, double depth);
	//draw a sprite with all possible options, including color
	void drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a, double depth);
	//draw a triangle part of a sprite
	void drawSpritePoly(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double depth);
	//draw a triangle part of a sprite rotated
	void drawSpritePolyRot(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double depth);
	//draw a triangle part of a sprite with all options, including color
	void drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a, double depth);

	void log(const char *str);
	void logError(const char *str);
	void logNotify(const char *str);

	int getKey(int i);
	int getMouse(int i);
	int getMousewheel_up();
	int getMousewheel_down();
	int getMouse_x();
	int getMouse_y();

	bool getKeyPress(int keyCode);
	bool getKeyRelease(int keyCode);
	bool getKeyHeld(int keyCode);
	bool getKeyIdle(int keyCode);

	void setSoundSampleDecompress(bool enabled);
	void setSoundSampleASync(bool enabled);
	void playSound(Audio* audio);
	void stopSound(Audio* audio);
	void pauseSound(Audio* audio);
	void unpauseSound(Audio* audio);
	void triggerSound(Audio* audio);
	void releaseSound(Audio* audio);

	void setSoundVolume(Audio* audio, double vol);
	void setSoundParameterValue(Audio* audio, const char* param, double value);
	void setSoundPitch(Audio* audio, double pitch);
	void setSoundTimePosition(Audio* audio, int position);

	void setAudioBusVolume(AudioBus* bus, double vol);
	double getAudioBusVolume(AudioBus* bus);

	float getSoundParameterValue(Audio* audio, const char* param);

	namespace Mouse
	{
		enum MouseButt { Mouse1, Mouse2, MouseMiddle, Mouse4, Mouse5 };
	};

	namespace Key
	{
		enum Key
		{
			Unknown = -1, ///< Unhandled key
			A = 0,        ///< The A key
			B,            ///< The B key
			C,            ///< The C key
			D,            ///< The D key
			E,            ///< The E key
			F,            ///< The F key
			G,            ///< The G key
			H,            ///< The H key
			I,            ///< The I key
			J,            ///< The J key
			K,            ///< The K key
			L,            ///< The L key
			M,            ///< The M key
			N,            ///< The N key
			O,            ///< The O key
			P,            ///< The P key
			Q,            ///< The Q key
			R,            ///< The R key
			S,            ///< The S key
			T,            ///< The T key
			U,            ///< The U key
			V,            ///< The V key
			W,            ///< The W key
			X,            ///< The X key
			Y,            ///< The Y key
			Z,            ///< The Z key
			Num0,         ///< The 0 key
			Num1,         ///< The 1 key
			Num2,         ///< The 2 key
			Num3,         ///< The 3 key
			Num4,         ///< The 4 key
			Num5,         ///< The 5 key
			Num6,         ///< The 6 key
			Num7,         ///< The 7 key
			Num8,         ///< The 8 key
			Num9,         ///< The 9 key
			Escape,       ///< The Escape key
			LControl,     ///< The left Control key
			LShift,       ///< The left Shift key
			LAlt,         ///< The left Alt key
			LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			RControl,     ///< The right Control key
			RShift,       ///< The right Shift key
			RAlt,         ///< The right Alt key
			RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			Menu,         ///< The Menu key
			LBracket,     ///< The [ key
			RBracket,     ///< The ] key
			SemiColon,    ///< The ; key
			Comma,        ///< The , key
			Period,       ///< The . key
			Quote,        ///< The ' key
			Slash,        ///< The / key
			BackSlash,    ///< The \ key
			Tilde,        ///< The ~ key
			Equal,        ///< The = key
			Dash,         ///< The - key
			Space,        ///< The Space key
			Return,       ///< The Return key
			BackSpace,    ///< The Backspace key
			Tab,          ///< The Tabulation key
			PageUp,       ///< The Page up key
			PageDown,     ///< The Page down key
			End,          ///< The End key
			Home,         ///< The Home key
			Insert,       ///< The Insert key
			Delete,       ///< The Delete key
			Add,          ///< The + key
			Subtract,     ///< The - key
			Multiply,     ///< The * key
			Divide,       ///< The / key
			Left,         ///< Left arrow
			Right,        ///< Right arrow
			Up,           ///< Up arrow
			Down,         ///< Down arrow
			Numpad0,      ///< The numpad 0 key
			Numpad1,      ///< The numpad 1 key
			Numpad2,      ///< The numpad 2 key
			Numpad3,      ///< The numpad 3 key
			Numpad4,      ///< The numpad 4 key
			Numpad5,      ///< The numpad 5 key
			Numpad6,      ///< The numpad 6 key
			Numpad7,      ///< The numpad 7 key
			Numpad8,      ///< The numpad 8 key
			Numpad9,      ///< The numpad 9 key
			F1,           ///< The F1 key
			F2,           ///< The F2 key
			F3,           ///< The F3 key
			F4,           ///< The F4 key
			F5,           ///< The F5 key
			F6,           ///< The F6 key
			F7,           ///< The F7 key
			F8,           ///< The F8 key
			F9,           ///< The F9 key
			F10,          ///< The F10 key
			F11,          ///< The F11 key
			F12,          ///< The F12 key
			F13,          ///< The F13 key
			F14,          ///< The F14 key
			F15,          ///< The F15 key
			Pause         ///< The Pause key
		};
	};
};