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

	//call
	SpriteSet* spriteSet(unsigned int i);//undocced
	inline SpriteSet* getSpriteSet(unsigned int i)//undocced
	{
		return spriteSet(i);
	}
	Sprite* spriteSetSprite(unsigned int i,unsigned int j);//undocced
	inline Sprite* getSprite(unsigned int i, unsigned int j)//undocced
	{
		return spriteSetSprite(i,j);
	}
	AudioSet* audioSet(unsigned int i);//undocced
	inline AudioSet* getAudioSet(unsigned int i)//undocced
	{
		return audioSet(i);
	}
	Audio* audioSetSound(unsigned int i, unsigned int j);//undocced
	inline Audio* getSound(unsigned int i, unsigned int j)//undocced
	{
		return audioSetSound(i, j);
	}
	FontSet* fontSet(unsigned int i);//undocced
	inline FontSet* getFontSet(unsigned int i)//undocced
	{
		return fontSet(i);
	}
	Font* fontSetFont(unsigned int i, unsigned int j);//undocced
	inline Font* getFont(unsigned int i, unsigned int j)//undocced
	{
		return fontSetFont(i, j);
	}

	int getSceneWidth();
	int getSceneHeight();

	void drawText(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a);//undocced
	inline void drawText(Font *font, std::string str, double x, double y, double size,double lineSpacing, double r, double g, double b, double a)//undocced
	{
		drawText(font, str.c_str(), x, y, size,lineSpacing, r, g, b, a);
	}
	inline void drawText(Font *font, const char* str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawText(font, str, x, y, size, 0, r, g, b, a);
	}
	inline void drawText(Font *font, std::string str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawText(font, str.c_str(), x, y, size, 0, r, g, b, a);
	}
	//draw sprite at position
	void drawSprite(Sprite* sprite, double x, double y);
	//draw sprite with size
	void drawSprite(Sprite* sprite, double x, double y, double w, double h);
	//draw a part of a sprite
	void drawSpritePart(Sprite* sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy);
	//draw a sprite rotated
	void drawSpriteRot(Sprite* sprite, double x, double y, double w, double h, double rot);
	//draw a sprite with all possible options, including color
	void drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a);
	//draw a triangle part of a sprite
	void drawSpritePoly(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3);
	//draw a triangle part of a sprite rotated
	void drawSpritePolyRot(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot);
	//draw a triangle part of a sprite with all options, including color
	void drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a);

	template<class T>
	T* at(T* t, double x, double y)//undocced
	{
		t->at(x, y);
		return t;
	}

	int getMousewheelUp();//undocced
	int getMousewheelDown();//undocced
	int getMouseX();//undocced
	int getMouseY();//undocced
	int getMouseWindowX();//undocced
	int getMouseWindowY();//undocced

	bool getMousePress(int i);//undocced
	bool getMouseRelease(int i);//undocced
	bool getMouseHeld(int i);//undocced
	bool getMouseIdle(int i);//undocced

	bool getKeyPressAny();//undocced
	bool getKeyReleaseAny();//undocced
	bool getKeyHeldAny();//undocced
	bool getKeyIdleAny();//undocced
	bool getKeyPress(int keyCode);//undocced
	bool getKeyRelease(int keyCode);//undocced
	bool getKeyHeld(int keyCode);//undocced
	bool getKeyIdle(int keyCode);//undocced

	void setSoundSampleDecompress(bool enabled);//undocced
	void setSoundSampleASync(bool enabled);//undocced
	void playSound(Audio* audio);//undocced
	void stopSound(Audio* audio);//undocced
	void pauseSound(Audio* audio);//undocced
	void unpauseSound(Audio* audio);//undocced
	void triggerSound(Audio* audio);//undocced
	void releaseSound(Audio* audio);//undocced

	void setSoundVolume(Audio* audio, double vol);//undocced
	void setSoundParameterValue(Audio* audio, const char* param, double value);//undocced
	void setSoundPitch(Audio* audio, double pitch);//undocced
	void setSoundTimePosition(Audio* audio, int position);//undocced

	void setAudioBusVolume(AudioBus* bus, double vol);//undocced
	double getAudioBusVolume(AudioBus* bus);//undocced
	void setAudioBusMute(AudioBus* bus, bool mute);//undocced
	bool getAudioBusMute(AudioBus* bus);//undocced

	float getSoundParameterValue(Audio* audio, const char* param);//undocced

	inline bool inside(double x,double y,double left, double top, double right, double bottom)//undocced
	{
		return (x >= left&&y >= top&&x < right&&y < bottom);
	}

	void destroyAllObjects();
	void exitGame();

	void setGameStartFunction(void(*func)(void));
	void setGameEndFunction(void(*func)(void));
	void setGameWindowResizeFunction(void(*func)(void));

	int random(int max);

	inline void beginTag(Tag *t)
	{
		SlaskEngine::instance()->beginTag(t);
	}
	inline void endTag(Tag *t)
	{
		SlaskEngine::instance()->endTag(t);
	}

	void log(const char *str);
	inline void log(std::string str)
	{
		log(str.c_str());
	}
	void logError(const char *str);
	inline void logError(std::string str)
	{
		logError(str.c_str());
	}
	void logNotify(const char *str);
	inline void logNotify(std::string str)
	{
		logNotify(str.c_str());
	}

	inline void deactivateCamera()
	{
		GraphicsHandler::instance()->setCamera(NULL);
	}
	inline Camera* getCamera()
	{
		return GraphicsHandler::instance()->getCamera();
	}
	inline double getCameraWidth()
	{
		return GraphicsHandler::instance()->getCameraW();
	}
	inline double getCameraHeight()
	{
		return GraphicsHandler::instance()->getCameraH();
	}
	inline double getCameraX()
	{
		return GraphicsHandler::instance()->getCameraX();
	}
	inline double getCameraY()
	{
		return GraphicsHandler::instance()->getCameraY();
	}

	void setTitle(const char* str);
	inline void setTitle(std::string str)
	{
		setTitle(str.c_str());
	}
	void setFPS(int fps);
	void enableVSync();
	void disableVSync();
	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWindowWidth();
	int getWindowHeight();
	bool setFullscreen(int w, int h);
	bool setWindowed(int w, int h);
	bool setFullscreenWindowed(int w, int h);

	int getResolutions();
	int getResolutionWidth(unsigned int i);
	int getResolutionHeight(unsigned int i);

	namespace Mouse//undocced
	{
		enum MouseButt { Mouse1, Mouse2, MouseMiddle, Mouse4, Mouse5 };
	};

	namespace Key//undocced
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