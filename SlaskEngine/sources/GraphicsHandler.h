#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "Sprite.h"
#include "Font.h"
#include "LogHandler.h"
#include <vector>

#define DEPTHRANGE (10000)

class Camera;

class GraphicsHandler
{
private:
	std::vector<sf::VideoMode> resolutions;
	sf::RenderWindow* window;
	sf::ContextSettings settings;
	bool vsync; 
	int framespersecond;
	const char* label;
	Camera *defaultCamera;
	Camera *activeCamera;
	bool queueCamera;

	int width;
	int height;

	inline void set_color(double r, double g, double b, double a);
	inline void restore_color();

	void initGL();

	GraphicsHandler() {}

public:
	static GraphicsHandler* instance();

	void init(const char* title);
	~GraphicsHandler();

	sf::RenderWindow* getWindow();
	
	void setTitle(const char* title);
	void setFPS(int fps);
	void setVSync(bool enabled);
	void setSize(int w, int h);
	void setRenderSize();
	void resize();

	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWidth();
	int getHeight();

	Camera* getCamera();
	void setCamera(Camera *cam);
	double getCameraX();
	double getCameraY();
	double getCameraW();
	double getCameraH();
	inline void refreshCamera()
	{
		queueCamera = 1;
	}

	int getResolutions();
	int getResolutionWidth(int i);
	int getResolutionHeight(int i);
	bool setFullscreen(int w,int h);
	bool setWindowed(int w, int h);
	bool setFullscreenWindowed(int w, int h);

	void drawSpriteExt(Sprite *sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a, double depth);
	void drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a, double depth);
	void drawBegin();
	void drawEnd();
	void close();
};

