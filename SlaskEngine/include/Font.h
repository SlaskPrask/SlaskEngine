#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <SFML/OpenGL.hpp>
#include <gl/freeglut.h>
#include "LogHandler.h"
#include "FontChar.h"

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
	unsigned int lineSize;
	unsigned int yOffset;
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

public:
	Font(const char* file);//undocced
	Font(const char* file,unsigned int size);//undocced
	inline unsigned int getSize()//undocced
	{
		return loadSize;
	}
	inline double getLineHeight(unsigned int fontsize)//undocced
	{
		return (double)lineSize*(double)loadSize/(double)fontsize;
	}
	inline FontChar *getChar(char c)
	{
		return &(ch[c]);
	}
	inline unsigned int getLineSize()
	{
		return lineSize;
	}
	inline unsigned int getOffset()
	{
		return yOffset;
	}
	~Font();
};
