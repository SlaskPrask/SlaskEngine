#pragma once
#include <gl/freeglut.h>

struct FontChar
{
	GLuint tex;
	int w, h;
	int bw, bh;
	int adv;
};
