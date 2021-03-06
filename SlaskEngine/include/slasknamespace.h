#pragma once
#include "SlaskEngine.h"

#define forInstances(OBJECT,CLASS) for(CLASS* OBJECT=static_cast<CLASS*>(CLASS::instance());OBJECT;OBJECT=static_cast<CLASS*>(CLASS::nextInstance())

namespace slask
{
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
#ifndef NO_AUDIO
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
#endif
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

	void drawText(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a);//undocced
	inline void drawText(Font *font, const std::string str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)//undocced
	{
		drawText(font, str.c_str(), x, y, size, lineSpacing, r, g, b, a);
	}
	inline void drawText(Font *font, const char* str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawText(font, str, x, y, size, 0, r, g, b, a);
	}
	inline void drawText(Font *font, const std::string str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawText(font, str.c_str(), x, y, size, 0, r, g, b, a);
	}

	void drawTextCenter(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a);//undocced
	inline void drawTextCenter(Font *font, const std::string str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)//undocced
	{
		drawTextCenter(font, str.c_str(), x, y, size, lineSpacing, r, g, b, a);
	}
	inline void drawTextCenter(Font *font, const char* str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawTextCenter(font, str, x, y, size, 0, r, g, b, a);
	}
	inline void drawTextCenter(Font *font,const std::string str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawTextCenter(font, str.c_str(), x, y, size, 0, r, g, b, a);
	}

	void drawTextRight(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a);//undocced
	inline void drawTextRight(Font *font, const std::string str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)//undocced
	{
		drawTextRight(font, str.c_str(), x, y, size, lineSpacing, r, g, b, a);
	}
	inline void drawTextRight(Font *font, const char* str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawTextRight(font, str, x, y, size, 0, r, g, b, a);
	}
	inline void drawTextRight(Font *font, const std::string str, double x, double y, double size, double r, double g, double b, double a)//undocced
	{
		drawTextRight(font, str.c_str(), x, y, size, 0, r, g, b, a);
	}

	void getKeyName(std::string *str, int keycode);
	void getMouseName(std::string *str, int i);
	void getKeyName(char *str, int keycode);
	void getMouseName(char *str, int i);

	//draw sprite at position
	void drawSprite(Sprite* sprite, double x, double y);//undocced
	//draw sprite with size
	void drawSprite(Sprite* sprite, double x, double y, double w, double h);//undocced
	//draw a part of a sprite
	void drawSpritePart(Sprite* sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy);//undocced
	//draw a sprite rotated
	void drawSpriteRot(Sprite* sprite, double x, double y, double w, double h, double rot);//undocced
	//draw a sprite with all possible options, including color
	void drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a);//undocced
	//draw a triangle part of a sprite
	void drawSpritePoly(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3);//undocced
	//draw a triangle part of a sprite rotated
	void drawSpritePolyRot(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot);//undocced
	//draw a triangle part of a sprite with all options, including color
	void drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a);//undocced

	void drawAnimationExt(Animation* anim,double x,double y,double w,double h,double rot,double r,double g,double b,double a);//undocced
	void drawAnimation(Animation* anim,double x,double y);//undocced
	inline void drawAnimation(Animation* anim,double x,double y,double w,double h)//undocced
	{
		drawAnimationExt(anim,x,y,w,h,0,1,1,1,1);
	}
	inline void drawAnimationRot(Animation* anim,double x,double y,double w,double h,double rot)//undocced
	{
		drawAnimationExt(anim,x,y,w,h,rot,1,1,1,1);
	}

	inline void drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a)//undocced
	{
		GraphicsHandler::instance()->drawRectangle(x, y, w, h, r, g, b, a);
	}

	template<class T>
	T* at(T* t, double x, double y)//undocced
	{
		t->at(x, y);
		return t;
	}

	template<class T>
	T* getInstance()//undocced
	{
		return static_cast<T*>(T::instance());
	}

	template<class T>
	T* getNextInstance()//undocced
	{
		return static_cast<T*>(T::nextInstance());
	}
#ifndef NO_AUDIO
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
	int getTimePosition(Audio* audio); //undocced
	bool getAudioIsPlaying(Audio* audio); //undocced
	float getSoundParameterValue(Audio* audio, const char* param);//undocced
#endif

	inline void clearKey(int keycode)//undocced
	{
		InputHandler::instance()->clearkey(keycode);
	}
	inline void clearKeyAny()//undocced
	{
		InputHandler::instance()->clearkeyany();
	}

	

	inline bool inside(double x,double y,double left, double top, double right, double bottom)//undocced
	{
		return (x >= left&&y >= top&&x < right&&y < bottom);
	}

	double textWidth(Font *font,const char* str,double size,double lineSpacing=0);
	inline double textWidth(Font *font,const std::string &str,double size,double lineSpacing=0)
	{
		return textWidth(font,str.c_str(),size,lineSpacing);
	}
	double textHeight(Font *font,const char* str,double size,double lineSpacing=0);
	inline double textHeight(Font *font,const std::string &str,double size,double lineSpacing=0)
	{
		return textHeight(font,str.c_str(),size,lineSpacing);
	}

	int getSceneWidth();
	int getSceneHeight();
	inline Scene* getScene()
	{
		return SlaskEngine::instance()->getCurrentScene();
	}
	inline double frameSeconds()
	{
		return SlaskEngine::instance()->getFrameSeconds();
	}
	inline double frameTime()
	{
		return SlaskEngine::instance()->getFrameMultiplier();
	}

	inline void enableTouchTranslation()
	{
		InputHandler::instance()->setTouchTranslation(1);
	}

	inline void disableTouchTranslation()
	{
		InputHandler::instance()->setTouchTranslation(0);
	}

	inline void setNoTouchPosition(int x, int y)
	{
		InputHandler::instance()->setNoTouchPosition(x, y);
	}
	inline void unsetNoTouchPosition()
	{
		InputHandler::instance()->unsetNoTouchPosition();
	}

	inline void keyboardTextBuffer(std::string *str, bool newlines = 0)
	{
		InputHandler::instance()->addKeyboardChar(str, newlines);
	}
	void keyboardTextBuffer(char *str, bool newlines = 0);

	int getMouseWheelUp();
	int getMouseWheelDown();
	double getMouseX();
	double getMouseY();
	int getMouseWindowX();
	int getMouseWindowY();

	bool getMousePress(int i);
	bool getMouseRelease(int i);
	bool getMouseHeld(int i);
	bool getMouseIdle(int i);

	inline bool getMouse(int i)
	{
		return getMouseHeld(i);
	}

	inline void clearMouseWheelUp()
	{
		InputHandler::instance()->clearmousewheel_up();
	}
	inline void clearMouseWheelDown()
	{
		InputHandler::instance()->clearmousewheel_down();
	}
	inline void clearMouse(int i)
	{
		InputHandler::instance()->clearmouse(i);
	}

	bool getKeyPressAny();
	bool getKeyReleaseAny();
	bool getKeyHeldAny();
	bool getKeyIdleAny();
	bool getKeyPress(int keyCode);
	bool getKeyRelease(int keyCode);
	bool getKeyHeld(int keyCode);
	bool getKeyIdle(int keyCode);


	inline bool getKey(int keyCode)
	{
		return getKeyHeld(keyCode);
	}

	inline bool getKeyAny()
	{
		return getKeyHeldAny();
	}

	bool getButtonPress(int joystick, int button);
	bool getButtonRelease(int joystick, int button);
	bool getButtonHeld(int joystick, int button);
	bool getButtonIdle(int joystick, int button);

	double getAxis(int joystick, int axis);

	inline bool getButton(int joystick, int button)
	{
		return getButtonHeld(joystick, button);
	}

	void destroyAllObjects();
	void exitGame();

	void setGameStartFunction(void(*func)(void));
	void setGameEndFunction(void(*func)(void));
	void setGameWindowResizeFunction(void(*func)(void));
	void setGameCloseFunction(void(*func)(void));

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
	inline void log(const std::string str)
	{
		log(str.c_str());
	}
	void logError(const char *str);
	inline void logError(const std::string str)
	{
		logError(str.c_str());
	}
	void logNotify(const char *str);
	inline void logNotify(const std::string str)
	{
		logNotify(str.c_str());
	}

	inline void windowScalingFit()
	{
		GraphicsHandler::instance()->scaleFit();
	}

	inline void windowScalingStretch()
	{
		GraphicsHandler::instance()->scaleStretch();
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
	inline void setTitle(const std::string str)
	{
		setTitle(str.c_str());
	}
	inline void enableMouseCursor()
	{
		GraphicsHandler::instance()->setMouseCursor(1);
	}
	inline void disableMouseCursor()
	{
		GraphicsHandler::instance()->setMouseCursor(0);
	}
	inline bool getMouseCursor()
	{
		return GraphicsHandler::instance()->getMouseCursor();
	}
	void setFPS(int fps);
	void enableVSync();
	void disableVSync();
	inline void getTitle(std::string *str)
	{
		*str = GraphicsHandler::instance()->getTitle();
	}
	void getTitle(char *str);
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

	namespace Mouse
	{
		enum MouseButt { Mouse1, Mouse2, Mouse3, Mouse4, Mouse5 };
	};
	namespace Mouse
	{
		enum MouseButtNames { MouseLeft, MouseRight, MouseMiddle };
	};

	namespace Key
	{
		enum Key
		{
			A=0,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
			Num0,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,
			Escape,
			LControl,LShift,LAlt,LSystem,
			RControl,RShift,RAlt,RSystem,
			Menu,
			LBracket,RBracket,
			SemiColon,
			Comma,
			Period,
			Quote,
			Slash,
			BackSlash,
			Tilde,
			Equal,
			Dash,
			Space,
			Return,
			BackSpace,
			Tab,
			PageUp,PageDown,
			End,Home,
			Insert,
			Delete,
			Add,
			Subtract,
			Multiply,
			Divide,
			Left,Right,Up,Down,
			Numpad0,Numpad1,Numpad2,Numpad3,Numpad4,Numpad5,Numpad6,Numpad7,Numpad8,Numpad9,
			F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,
			Pause
		};
	};

	void dumpObjects();//undocced
	void dumpDepths();//undocced
	void dumpDepthQueue();//undocced
	void dumpDepthChangeQueue();//undocced
	void dumpObj(Object *obj);//undocced
};