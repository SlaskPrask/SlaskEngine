#include "../include/SlaskNamespace.h"

SpriteSet* slask::spriteSet(unsigned int i)
{
	return SlaskEngine::instance()->spriteSet(i);
}

Sprite* slask::spriteSetSprite(unsigned int i, unsigned int j)
{
	SpriteSet *ss = SlaskEngine::instance()->spriteSet(i);
	if (ss)
	return ss->get(j);
	else
	return NULL;
}

#ifndef NO_AUDIO
AudioSet* slask::audioSet(unsigned int i)
{
	return SlaskEngine::instance()->audioSet(i);
}

Audio* slask::audioSetSound(unsigned int i, unsigned int j)
{
	AudioSet *ss = SlaskEngine::instance()->audioSet(i);
	if (ss)
		return ss->get(j);
	else
		return NULL;
}
#endif

FontSet* slask::fontSet(unsigned int i)
{
	return SlaskEngine::instance()->fontSet(i);
}

Font* slask::fontSetFont(unsigned int i, unsigned int j)
{
	FontSet *ss = SlaskEngine::instance()->fontSet(i);
	if (ss)
		return ss->get(j);
	else
		return NULL;
}

int slask::getSceneWidth()
{
	Scene *s = SlaskEngine::instance()->getCurrentScene();
	if (s)
		return s->width;
	else
	{
		LogHandler::notify("Engine", "Unable to obtain scene width, no active scene.");
		return 1;
	}
}

int slask::getSceneHeight()
{
	Scene *s = SlaskEngine::instance()->getCurrentScene();
	if (s)
		return s->height;
	else
	{
		LogHandler::notify("Engine","Unable to obtain scene height, no active scene.");
		return 1;
	}
}

void slask::destroyAllObjects()
{
	SlaskEngine::instance()->deleteAllObjects();
}

void slask::exitGame()
{
	SlaskEngine::instance()->gameEnd();
}

void slask::setGameStartFunction(void(*func)(void))
{
	SlaskEngine::setGameStartFunc(func);
}

void slask::setGameEndFunction(void(*func)(void))
{
	SlaskEngine::setGameEndFunc(func);
}

void slask::setGameWindowResizeFunction(void(*func)(void))
{
	SlaskEngine::setGameWindowResizeFunc(func);
}

void slask::setGameCloseFunction(void(*func)(void))
{
	SlaskEngine::setGameCloseFunc(func);
}

void slask::setTitle(const char* title)
{
	GraphicsHandler::instance()->setTitle(title);
}
void slask::setFPS(int fps)
{
	if (fps < 0)
		fps = 0;
	GraphicsHandler::instance()->setFPS(fps);
	SlaskEngine::instance()->setFPS(fps);
}
void slask::enableVSync()
{
	GraphicsHandler::instance()->setVSync(1);
}
void slask::disableVSync()
{
	GraphicsHandler::instance()->setVSync(0);
}

int slask::random(int max)
{
	return rand()%(max+1);
}

void slask::getTitle(char *str)
{
	std::string s;
	getTitle(&s);
	strcpy(str, s.c_str());
}
void slask::keyboardTextBuffer(char *str, bool newlines)
{
	std::string s;
	InputHandler::instance()->addKeyboardChar(&s,newlines);
	strcpy(str, s.c_str());
}
int slask::getFPS()
{
	return GraphicsHandler::instance()->getFPS();
}
bool slask::getVSync()
{
	return GraphicsHandler::instance()->getVSync();
}
int slask::getWindowWidth()
{
	return GraphicsHandler::instance()->getWidth();
}
int slask::getWindowHeight()
{
	return GraphicsHandler::instance()->getHeight();
}

int slask::getResolutions()
{
	return GraphicsHandler::instance()->getResolutions();
}
int slask::getResolutionWidth(unsigned int i)
{
	return GraphicsHandler::instance()->getResolutionWidth(i);
}
int slask::getResolutionHeight(unsigned int i)
{
	return GraphicsHandler::instance()->getResolutionHeight(i);
}
bool slask::setFullscreen(int w, int h)
{
	return GraphicsHandler::instance()->setFullscreen(w,h);
}
bool slask::setWindowed(int w, int h)
{
	return GraphicsHandler::instance()->setWindowed(w,h);
}
bool slask::setFullscreenWindowed(int w, int h)
{
	return GraphicsHandler::instance()->setFullscreenWindowed(w,h);
}

void slask::drawText(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)
{
	return GraphicsHandler::instance()->drawText(font, str, x, y, size, lineSpacing, 1, r, g, b, a);
}

void slask::drawTextCenter(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)
{
	return GraphicsHandler::instance()->drawText(font, str, x, y, size, lineSpacing, 0, r, g, b, a);
}

void slask::drawTextRight(Font *font, const char* str, double x, double y, double size, double lineSpacing, double r, double g, double b, double a)
{
	return GraphicsHandler::instance()->drawText(font, str, x, y, size, lineSpacing, -1, r, g, b, a);
}

void slask::drawSprite(Sprite* sprite, double x, double y)
{
	if (!sprite)
	{
		LogHandler::notify("Graphics","Attempting to draw unloaded sprite.");
		return;
	}
	GraphicsHandler::instance()->drawSpriteExt(sprite, x, y, sprite->getWidth(), sprite->getHeight(), 0, 0, 1, 1, 0, 1, 1, 1, -1);
}

void slask::drawSprite(Sprite* sprite, double x, double y, double w, double h)
{
	GraphicsHandler::instance()->drawSpriteExt(sprite, x, y, w, h, 0, 0, 1, 1, 0, 1, 1, 1, -1);
}

void slask::drawSpritePart(Sprite* sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy)
{
	GraphicsHandler::instance()->drawSpriteExt(sprite, x, y, w, h, fromx, fromy, tox, toy, 0, 1, 1, 1, -1);
}

void slask::drawSpriteRot(Sprite* sprite, double x, double y, double w, double h, double rot)
{
	GraphicsHandler::instance()->drawSpriteExt(sprite, x, y, w, h, 0, 0, 1, 1, rot, 1, 1, 1, -1);
}

void slask::drawSpritePoly(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3)
{
	GraphicsHandler::instance()->drawSpritePolyExt(sprite, x1, y1, x2, y2, x3, y3, texx1, texy1, texx2, texy2, texx3, texy3, 0, 1, 1, 1, -1);
}

void slask::drawSpritePolyRot(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot)
{
	GraphicsHandler::instance()->drawSpritePolyExt(sprite, x1, y1, x2, y2, x3, y3, texx1, texy1, texx2, texy2, texx3, texy3, rot, 1, 1, 1, -1);
}

void slask::drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a)
{
	GraphicsHandler::instance()->drawSpriteExt(sprite, x, y, w, h, fromx, fromy, tox, toy, rot, r, g, b, a);
}

void slask::drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a)
{
	GraphicsHandler::instance()->drawSpritePolyExt(sprite, x1, y1, x2, y2, x3, y3, texx1, texy1, texx2, texy2, texx3, texy3, rot, r, g, b, a);
}

void slask::drawAnimationExt(Animation* anim,double x,double y,double w,double h,double rot,double r,double g,double b,double a)
{
	if (!anim->getSprite())
	{
		LogHandler::notify("Graphics","Attempting to draw unloaded sprite for animation.");
		return;
	}
	GraphicsHandler::instance()->drawSpriteExt(anim->getSprite(),x,y,w,h,anim->getFromX(),anim->getFromY(),anim->getToX(),anim->getToY(),rot,r,g,b,a);
}

void slask::drawAnimation(Animation* anim,double x,double y)
{
	drawAnimationExt(anim,x,y,anim->getWidth(),anim->getHeight(),0,1,1,1,1);
}

void slask::log(const char *str)
{
	LogHandler::instance()->log(str);
}

void slask::logError(const char *str)
{
	LogHandler::instance()->error(str);
}

void slask::logNotify(const char *str)
{
	LogHandler::instance()->notify(str);
}

bool slask::getMousePress(int i)
{
	if (InputHandler::instance()->clearedmouse(i))
		return 0;
	return InputHandler::instance()->getmouse(i)==1;
}
bool slask::getMouseRelease(int i)
{
	if (InputHandler::instance()->clearedmouse(i))
		return 0;
	return (InputHandler::instance()->getmouse(i)==-1);
}
bool slask::getMouseHeld(int i)
{
	if (InputHandler::instance()->clearedmouse(i))
		return 0;
	return (InputHandler::instance()->getmouse(i)>0);
}
bool slask::getMouseIdle(int i)
{
	if (InputHandler::instance()->clearedmouse(i))
		return 1;
	return (InputHandler::instance()->getmouse(i)<=0);
}
int slask::getMouseWheelUp()
{
	if (InputHandler::instance()->clearedmousewheel_up())
		return 0;
	return InputHandler::instance()->getmousewheel_up();
}
int slask::getMouseWheelDown()
{
	if (InputHandler::instance()->clearedmousewheel_down())
		return 0;
	return InputHandler::instance()->getmousewheel_down();
}

double slask::getMouseX()
{
	return InputHandler::instance()->getmouse_camera_x();
}

double slask::getAxis(int joystick, int axis)
{
	return InputHandler::instance()->getaxis(joystick, axis);
}


double slask::getMouseY()
{
	return InputHandler::instance()->getmouse_camera_y();
}
int slask::getMouseWindowX()
{
	return InputHandler::instance()->getmouse_x();
}
int slask::getMouseWindowY()
{
	return InputHandler::instance()->getmouse_y();
}

bool slask::getKeyPressAny()
{
	if (InputHandler::instance()->clearedkeyany())
		return 0;
	return InputHandler::instance()->getanykey(1);
}
bool slask::getKeyReleaseAny()
{
	if (InputHandler::instance()->clearedkeyany())
		return 0;
	return InputHandler::instance()->getanykey(-1);
}
bool slask::getKeyHeldAny()
{
	if (InputHandler::instance()->clearedkeyany())
		return 0;
	return InputHandler::instance()->getanykey(2);
}
bool slask::getKeyIdleAny()
{
	if (InputHandler::instance()->clearedkeyany())
		return 1;
	return InputHandler::instance()->getanykey(0);
}

bool slask::getKeyPress(int keyCode)
{
	if (InputHandler::instance()->clearedkey(keyCode))
		return 0;
	return (InputHandler::instance()->getkey(keyCode)==1);
}
bool slask::getKeyRelease(int keyCode)
{
	if (InputHandler::instance()->clearedkey(keyCode))
		return 0;
	return (InputHandler::instance()->getkey(keyCode)==-1);
}
bool slask::getKeyHeld(int keyCode)
{
	if (InputHandler::instance()->clearedkey(keyCode))
		return 0;
	return (InputHandler::instance()->getkey(keyCode)>0);
}
bool slask::getKeyIdle(int keyCode)
{
	if (InputHandler::instance()->clearedkey(keyCode))
		return 1;
	return (InputHandler::instance()->getkey(keyCode)<=0);
}

bool slask::getButtonPress(int joystick, int button)
{
	if (InputHandler::instance()->clearedjoy(joystick, button))
		return 0;
	return (InputHandler::instance()->getbutton(joystick, button) == 1);
}

bool slask::getButtonRelease(int joystick, int button)
{
	if (InputHandler::instance()->clearedjoy(joystick, button))
		return 0;
	return (InputHandler::instance()->getbutton(joystick, button) == -1);
}
bool slask::getButtonHeld(int joystick, int button)
{
	if (InputHandler::instance()->clearedjoy(joystick, button))
		return 0;
	return (InputHandler::instance()->getbutton(joystick, button) >0);
}
bool slask::getButtonIdle(int joystick, int button)
{
	if (InputHandler::instance()->clearedjoy(joystick, button))
		return 1;
	return (InputHandler::instance()->getbutton(joystick, button) <= 0);
}


#ifndef NO_AUDIO
void slask::setSoundSampleDecompress(bool enabled)
{
	AudioHandler::instance()->setSampleDecompress(enabled);
}
void slask::setSoundSampleASync(bool enabled)
{
	AudioHandler::instance()->setSampleASync(enabled);
}
void slask::playSound(Audio* audio)
{
	AudioHandler::instance()->play(audio);
}
void slask::stopSound(Audio* audio)
{
	AudioHandler::instance()->stop(audio);
}
void slask::pauseSound(Audio* audio)
{
	AudioHandler::instance()->pause(audio);
}
void slask::unpauseSound(Audio* audio)
{
	AudioHandler::instance()->unpause(audio);
}
void slask::triggerSound(Audio* audio)
{
	AudioHandler::instance()->trigger(audio);
}
void slask::releaseSound(Audio* audio)
{
	AudioHandler::instance()->release(audio);
}

void slask::setSoundVolume(Audio* audio, double vol)
{
	AudioHandler::instance()->setVolume(audio,vol);
}
void slask::setSoundParameterValue(Audio* audio, const char* param, double value)
{
	AudioHandler::instance()->setParameterValue(audio,param,value);
}
void slask::setSoundPitch(Audio* audio, double pitch)
{
	AudioHandler::instance()->setPitch(audio,pitch);
}
void slask::setSoundTimePosition(Audio* audio, int position)
{
	AudioHandler::instance()->setTimePosition(audio,position);
}
void slask::setAudioBusVolume(AudioBus* bus, double vol)
{
	AudioHandler::instance()->setBusVolume(bus,vol);
}
double slask::getAudioBusVolume(AudioBus* bus)
{
	return AudioHandler::instance()->getBusVolume(bus);
}
void slask::setAudioBusMute(AudioBus* bus, bool mute)
{
	AudioHandler::instance()->setBusMute(bus, mute);
}
bool slask::getAudioBusMute(AudioBus* bus)
{
	return AudioHandler::instance()->getBusMute(bus);
}
float slask::getSoundParameterValue(Audio* audio, const char* param)
{
	return AudioHandler::instance()->getParameterValue(audio,param);
}

int slask::getTimePosition(Audio* audio)
{
	return AudioHandler::instance()->getTimePosition(audio);
}

bool slask::getAudioIsPlaying(Audio* audio)
{
	return AudioHandler::instance()->getIsPlaying(audio);
}
#endif

double slask::textWidth(Font *font,const char* str,double size,double lineSpacing)
{
	if (!font)
	{
		LogHandler::notify("Graphics","Attempting to use unloaded font.");
		return 0;
	}

	std::string ln(str);
	if (ln.length()==0)
		return 0;

	GLfloat lineHeight = (GLfloat)font->getLineSize();
	GLfloat yOffset = (GLfloat)font->getOffset();
	GLfloat scale = (GLfloat)size / (GLfloat)font->getSize();
	double maxw=0;

	std::stringstream ss(ln);
	while (std::getline(ss,ln,'\n'))
	{
		GLfloat offset = 0;
		for (unsigned int i = 0; i < ln.size(); i++)
		{
			offset += font->getChar(ln[i])->adv;
		}
		if (offset*scale>maxw)
			maxw=offset*scale;
	}

	return maxw;
}

double slask::textHeight(Font *font,const char* str,double size,double lineSpacing)
{
	if (!font)
	{
		LogHandler::notify("Graphics","Attempting to use unloaded font.");
		return 0;
	}

	std::string ln(str);
	if (ln.length()==0)
		return 0;

	GLfloat lineHeight = (GLfloat)font->getLineSize();
	GLfloat yOffset = (GLfloat)font->getOffset();
	GLfloat scale = (GLfloat)size / (GLfloat)font->getSize();
	double maxw=0;

	int lines=0;
	std::stringstream ss(ln);
	while (std::getline(ss,ln,'\n'))
	{
		lines++;
	}

	return yOffset*scale + (lines-1)*(lineSpacing + (lineHeight)*scale);
}

void slask::dumpObjects()
{
	#ifdef SLASKDEBUG
	SlaskEngine::instance()->dumpObjects();
	#endif
}
void slask::dumpDepths()
{
	#ifdef SLASKDEBUG
	SlaskEngine::instance()->dumpDepths();
	#endif
}
void slask::dumpDepthQueue()
{
	#ifdef SLASKDEBUG
	SlaskEngine::instance()->dumpDepthQueue();
	#endif
}
void slask::dumpDepthChangeQueue()
{
	#ifdef SLASKDEBUG
	SlaskEngine::instance()->dumpDepthChangeQueue();
	#endif
}
void slask::dumpObj(Object *obj)
{
	#ifdef SLASKDEBUG
	SlaskEngine::instance()->dumpObj(obj);
	#endif
}
