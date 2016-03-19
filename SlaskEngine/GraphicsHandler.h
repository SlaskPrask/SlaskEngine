#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "Sprite.h"


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
	GraphicsHandler(int w, int h, const char* title);
	~GraphicsHandler();

	sf::RenderWindow* getWindow();
	
	void setTitle(const char* title);
	void setFPS(int fps);
	void setVSync(bool enabled);
	void setSize(int w, int h);
	
	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWidth();
	int getHeight();
	
	void drawBegin();
	void drawEnd();
	void close();

	void drawSprite(Sprite* sprite, int x, int y);
};

