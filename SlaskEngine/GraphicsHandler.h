#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "Sprite.h"
#include "Font.h"


class GraphicsHandler
{
private:
	sf::RenderWindow* window;
	bool vsync; 
	int framespersecond;
	const char* label;

	int width;
	int height;

public:
	static GraphicsHandler* instance();

	void init(int w, int h, const char* title);
	~GraphicsHandler();

	sf::RenderWindow* getWindow();
	
	void setTitle(const char* title);
	void setFPS(int fps);
	void setVSync(bool enabled);
	void setSize(int w, int h);
	void setRenderSize(int w, int h);
	
	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWidth();
	int getHeight();
	
	void drawSprite(Sprite* sprite, double x, double y, double w, double h);

	void drawBegin();
	void drawEnd();
	void close();
};

