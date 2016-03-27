#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "Sprite.h"
#include "Font.h"

#define DEPTHRANGE (10000)

class GraphicsHandler
{
private:
	sf::RenderWindow* window;
	bool vsync; 
	int framespersecond;
	const char* label;

	int width;
	int height;

	inline void set_color(double r, double g, double b, double a);
	inline void restore_color();

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
	void resize();

	const char* getTitle();
	int getFPS();
	bool getVSync();
	int getWidth();
	int getHeight();

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
	void drawBegin();
	void drawEnd();
	void close();
};

