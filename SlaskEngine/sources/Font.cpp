#include "Font.h"
#include "GraphicsHandler.h"

void Font::load(const char* file)
{
	fileName = file;
	height = 0;
	ch = new FontChar[128];

	FT_Library *lib = GraphicsHandler::instance()->getFontLib();

	if (!lib)
	return;

	FT_Face face;
	if (FT_New_Face(*lib, file, 0, &face))
	{
		std::string str = "Unable to load font from file \"";
		str += file;
		str += '\"';
		LogHandler::error("Graphics", str.c_str());
		return;
	}

	FT_Set_Char_Size(face, loadSize << 6, loadSize << 6, 96, 96);
	height = loadSize;
	list = glGenLists(128);
	for (unsigned char i = 0; i < 128; i++)
	glGenTextures(1, &(ch[i].tex));
	for (unsigned char i = 0; i < 128; i++)
	if (!charToGL(face, i))
	break;
	
	FT_Done_Face(face);
}

Font::Font(const char* file)
{
	loadSize = _SLASK_DEFAULT_FONT_LOAD_SIZE;
	load(file);
}

Font::Font(const char* file,unsigned int size)
{
	loadSize = size;
	load(file);
}

bool Font::charToGL(FT_Face face, char c)
{
	if (FT_Load_Glyph(face, FT_Get_Char_Index(face, c), FT_LOAD_DEFAULT))
	{
		std::string str = "Unable to load font data from \"";
		str += fileName;
		str += "\"";
		LogHandler::error("Graphics", str.c_str());
		return 0;
	}
	FT_Glyph glyph;
	if (FT_Get_Glyph(face->glyph, &glyph))
	{
		std::string str = "Unable to get font data from \"";
		str += fileName;
		str += "\"";
		LogHandler::error("Graphics", str.c_str());
		return 0;
	}

	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bmpg = (FT_BitmapGlyph)glyph;
	FT_Bitmap &bmp = bmpg->bitmap;

	unsigned int w = power2(bmp.width);
	unsigned int h = power2(bmp.rows);
	GLubyte *data = new GLubyte[2 * w*h];
	for (unsigned int j = 0; j < h; j++)
		for (unsigned int i = 0; i < w; i++)
		{
			data[2 * (i + j*w)] = data[2 * (i + j*w) + 1] = (i >= bmp.width || j >= bmp.rows) ? 0 : bmp.buffer[i + bmp.width*j];
		}

	FT_Render_Glyph(face->glyph, ft_render_mode_normal);
	ch[c].adv = face->glyph->advance.x;
	ch[c].w = w;
	ch[c].h = h;
	ch[c].bw = face->glyph->bitmap_left;
	ch[c].bh = face->glyph->bitmap_top;
	
	glBindTexture(GL_TEXTURE_2D, ch[c].tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);

	glNewList(list + c, GL_COMPILE);//TODO: IF THIS FAILS                                                                                                      ***********
	glBindTexture(GL_TEXTURE_2D, ch[c].tex);
	glPushMatrix();
	glTranslatef((GLfloat)bmpg->left, (GLfloat)bmpg->top - (GLfloat)bmp.rows, 0);
	double x = (double)bmp.width / (double)w;
	double y = (double)bmp.rows / (double)h;
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2f(0, (GLfloat)bmp.rows);
	glTexCoord2d(0, (GLfloat)y);
	glVertex2f(0, 0);
	glTexCoord2d((GLfloat)x, 0);
	glVertex2f((GLfloat)bmp.width, 0);
	glTexCoord2d((GLfloat)x, y);
	glVertex2f((GLfloat)bmp.width, (GLfloat)bmp.rows);
	glEnd();
	glPopMatrix();
	glTranslatef((GLfloat)(face->glyph->advance.x >> 6), 0, 0);
	glEndList();

	delete[] data;
	return 1;
}

Font::~Font()
{
	glDeleteLists(list, 128);
	for (unsigned char i = 0; i < 128; i++)
	glDeleteTextures(1, &(ch[i].tex));
	delete[] ch;
}
