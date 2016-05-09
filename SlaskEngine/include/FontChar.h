#pragma once
#include <gl/freeglut.h>

struct FontChar
{
	GLuint tex;
	GLfloat w, h;
	GLfloat bw, bh;
	GLfloat adv;
};
