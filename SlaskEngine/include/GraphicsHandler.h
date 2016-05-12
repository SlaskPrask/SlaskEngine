#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include "Sprite.h"
#include "Font.h"
#include "LogHandler.h"
#include <vector>

#ifndef  GL_CLAMP_TO_EDGE
#define  GL_CLAMP_TO_EDGE 0x812F
#endif

#define _SLASK_DEFAULT_FPS (60)

#define _SLASK_DEPTHRANGE (10000)
#define _SLASK_DEFAULT_DRAW_DEPTH (-10000)

class Camera;

class GraphicsHandler
{
private:
	std::vector<sf::VideoMode> resolutions;
	sf::RenderWindow* window;
	sf::ContextSettings settings;
	FT_Library *fontLib;
	bool vsync; 
	int framespersecond;
	bool cursorOn;
	std::string label;
	Camera *defaultCamera;
	Camera *activeCamera;
	bool queueCamera;
	bool blackBars;
	double horBars, verBars;
	GLfloat blackBarData[12],squareData[12];
	double regionW, regionH;

	int width;
	int height;

	inline void set_color(double r, double g, double b, double a);
	inline void restore_color();

	void initGL();

	GLfloat drawDepth;

	GraphicsHandler() {}

public:
	inline static GraphicsHandler* instance()
	{
		static GraphicsHandler graphicshandler;
		return &graphicshandler;
	}

	void init(const char* title);
	~GraphicsHandler();

	inline int getWidth()
	{
		return width;
	}

	inline int getHeight()
	{
		return height;
	}

	inline int getFPS()
	{
		return framespersecond;
	}

	inline bool getVSync()
	{
		return vsync;
	}

	inline std::string getTitle()
	{
		return label;
	}

	inline sf::RenderWindow* getWindow()
	{
		return window;
	}

	inline FT_Library* getFontLib()
	{
		return fontLib;
	}

	double getCameraX();
	double getCameraY();
	double getCameraW();
	double getCameraH();
	
	void setTitle(const char* title);
	void setFPS(int fps);
	void setVSync(bool enabled);
	void setSize(int w, int h);
	void setRenderSize();
	void resize();

	inline double getVerBar()
	{
		if (blackBars)
			return verBars;
		return 0;
	}

	inline double getHorBar()
	{
		if (blackBars)
			return horBars;
		else
			return 0;
	}

	inline double getRegionW()
	{
		return regionW;
	}
	inline double getRegionH()
	{
		return regionH;
	}

	void setMouseCursor(bool enabled);
	inline bool getMouseCursor()
	{
		return cursorOn;
	}

	Camera* getCamera();
	void setCamera(Camera *cam);
	inline void refreshCamera()
	{
		queueCamera = 1;
	}
	void earlyCameraRefresh();

	inline void scaleFit()
	{
		if (!blackBars)
			refreshCamera();
		blackBars = 1;
	}
	inline void scaleStretch()
	{
		if (blackBars)
			refreshCamera();
		blackBars = 0;
	}

	int getResolutions();
	int getResolutionWidth(unsigned int i);
	int getResolutionHeight(unsigned int i);
	bool setFullscreen(int w,int h);
	bool setWindowed(int w, int h);
	bool setFullscreenWindowed(int w, int h);

	void GraphicsHandler::drawText(Font *font, const char* str, double x, double y, double size, double lineSpacing,int align, double r, double g, double b, double a);
	void drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a);
	void drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a);
	void drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a);
	void drawBegin();
	void drawEnd();
	void close();
};

