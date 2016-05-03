#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "../include/LogHandler.h"
#include "../include/FontChar.h"

#ifndef  GL_CLAMP_TO_EDGE
 #define  GL_CLAMP_TO_EDGE 0x812F
#endif
#define _SLASK_DEFAULT_FONT_LOAD_SIZE (64)

class GraphicsHandler;

class Font //undocced
{
	friend class GraphicsHandler;
private:
	GLuint list;
	FontChar *ch;
	unsigned int loadSize;
	void load(const char* file);
	std::string fileName;
	unsigned int height;
	inline static int power2(int i)
	{
		int val = 1;
		while (val < i)val <<=1;
		return val;
	}
	bool charToGL(FT_Face face, char c);
	inline FontChar *getChar(char c)
	{
		return &(ch[c]);
	}

public:
	Font(const char* file);
	Font(const char* file,unsigned int size);
	inline unsigned int getSize()
	{
		return loadSize;
	}
	~Font();
};
