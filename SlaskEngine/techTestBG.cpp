#pragma once
#include "techTestBG.h"

using namespace slask;

testBG::testBG()
{
	sprite = getSprite(0, 0);
	windowHeight = getWindowHeight();
	windowWidth = getWindowWidth();
}

void testBG::run()
{
}

void testBG::draw()
{
	//the big at the back, stretched
	drawSprite(sprite, 10, 10, windowWidth - 20, windowHeight - 20, 1000);
	/*//small not moving, static position
	drawSprite(sprite, 100, 100, 1);
	//rolling one, static position
	drawSprite(sprite, 100 + cos(position*3.14159265 / 180.0f) * 100, 100 + sin(position*3.14159265 / 180.0f) * 100, 10);
	//spinning whole, static position
	drawSpriteRot(sprite, 300, 150, 100, 100, position, -10);
	//spinning red, static position
	drawSpriteExt(sprite, 150, 400, 200, 100, 0, 0, .5, .5, -position, 1, 0, 0, 0.5, -20);
	//top left, dynamic position
	drawSpritePoly(sprite, 0, 0, 100, 0, 0, 100, .5, 0, 0, 1, 1, 1, -100);
	//top right, dynamic position
	drawSpritePoly(sprite, windowWidth, 0, windowWidth, 100, windowWidth - 100, 0, .5, 0, 0, 1, 1, 1, -100);
	//bottom left, dynamic position
	drawSpritePoly(sprite, 0, windowHeight, 0, windowHeight - 100, 100, windowHeight, .5, 0, 0, 1, 1, 1, -100);
	//bottom right, dynamic position
	drawSpritePoly(sprite, windowWidth, windowHeight, windowWidth - 100, windowHeight, windowWidth, windowHeight - 100, .5, 0, 0, 1, 1, 1, -100);
	//spinning green, static position
	drawSpritePolyExt(sprite, 300, 200, 200, 400, 400, 400, .5, 0, 0, 1, 1, 1, position*2.0f, 0, 1, 0, 1, -100);*/

}