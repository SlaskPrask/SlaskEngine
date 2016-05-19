#include "../include/GraphicsHandler.h"
#include "../include/Camera.h"

//TODO: window checks

void GraphicsHandler::init(const char* title)
{
	LogHandler::log("Graphics", "Start");

	defaultCamera = new Camera();
	activeCamera = defaultCamera;
	queueCamera = 0;

	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	resolutions = sf::VideoMode::getFullscreenModes();

	window = 0;
	framespersecond = _SLASK_DEFAULT_FPS;
	vsync = true;
	label = title;
	cursorOn = 1;
	width = height = 0;
	regionW = regionH;

	blackBarData[0] = 0;
	blackBarData[1] = 0;
	blackBarData[2] = _SLASK_DEFAULT_DRAW_DEPTH;
	blackBarData[3] = 0;
	blackBarData[4] = 0;
	blackBarData[5] = _SLASK_DEFAULT_DRAW_DEPTH;
	blackBarData[6] = 0;
	blackBarData[7] = 0;
	blackBarData[8] = _SLASK_DEFAULT_DRAW_DEPTH;
	blackBarData[9] = 0;
	blackBarData[10] = 0;
	blackBarData[11] = _SLASK_DEFAULT_DRAW_DEPTH;
	squareData[0] = 0;
	squareData[1] = 0;
	squareData[2] = _SLASK_DEFAULT_DRAW_DEPTH;
	squareData[3] = 1;
	squareData[4] = 0;
	squareData[5] = _SLASK_DEFAULT_DRAW_DEPTH;
	squareData[6] = 0;
	squareData[7] = 1;
	squareData[8] = _SLASK_DEFAULT_DRAW_DEPTH;
	squareData[9] = 1;
	squareData[10] = 1;
	squareData[11] = _SLASK_DEFAULT_DRAW_DEPTH;

	drawDepth = _SLASK_DEFAULT_DRAW_DEPTH;

	blackBars = 1;
	horBars=verBars=0;

	initGL();

	fontLib=new FT_Library();
	if (FT_Init_FreeType(fontLib))
	{
		fontLib = NULL;
		LogHandler::error("Graphics", "Unable to initialize fonts.");
		return;
	}

	LogHandler::log("Graphics", "Initialized");
}

void GraphicsHandler::initGL()
{
	if (window)
	{
		setVSync(vsync);
		setFPS(framespersecond);
		setMouseCursor(cursorOn);

		window->setActive();
	}

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//todo alpha blending fix
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//todo drawing nice with culling maybe?
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Camera* GraphicsHandler::getCamera()
{
	if (activeCamera == defaultCamera)
		return NULL;
	else
		return activeCamera;
}

void GraphicsHandler::setCamera(Camera *cam)
{
	if (cam != activeCamera)
	{
		refreshCamera();
		if (cam == NULL)
			activeCamera = defaultCamera;
		else
			activeCamera = cam;
	}
}

bool GraphicsHandler::setFullscreen(int w, int h)
{
	bool valid = false;
	for (unsigned int i = 0; i < resolutions.size();i++)
	if (resolutions[i].width == w && resolutions[i].height == h)
	{
		valid = true;
		break;
	}

	if (!valid)
	{
		std::string str = "Attempted to switch to unsupported resolution ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::notify("Graphics", str.c_str());
		return false;
	}

	close();

#ifdef MAC
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::Fullscreen);
#else
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::Fullscreen, settings);
#endif

	if (!window)
	{
		std::string str = "Unable change to supported fullscreen resolution ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::error("Graphics", str.c_str());
		return false;
	}
	else
	{
		std::string str = "Changed to fullscreen resolution ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::log("Graphics", str.c_str());

		setSize(w, h);
		initGL();
		return true;
	}
}

bool GraphicsHandler::setWindowed(int w, int h)
{
	close();


#ifdef MAC
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::Default);
#else
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::Default, settings);
#endif

	if (!window)
	{
		std::string str = "Unable change to window ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::error("Graphics", str.c_str());
		return false;
	}
	else
	{
		std::string str = "Changed to window ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::log("Graphics", str.c_str());

		setSize(w, h);
		initGL();
		return true;
	}
}

bool GraphicsHandler::setFullscreenWindowed(int w, int h)
{
	close();

#ifdef MAC
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::None);
#else
	window = new sf::RenderWindow(sf::VideoMode(w, h), getTitle(), sf::Style::None, settings);
#endif

	window->setPosition(sf::Vector2i(0, 0));

	if (!window)
	{
		std::string str = "Unable change to fullscreen windowed ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::error("Graphics", str.c_str());
		return false;
	}
	else
	{
		std::string str = "Changed to fullscreen windowed ";
		str += std::to_string(w);
		str += 'x';
		str += std::to_string(h);
		LogHandler::log("Graphics", str.c_str());

		setSize(w, h);
		initGL();
		return true;
	}
}

void GraphicsHandler::setTitle(const char* title)
{
	label = title;
	if (window)
	window->setTitle(title);
}

void GraphicsHandler::setFPS(int fps)
{
	framespersecond = fps;
	if (window)
		window->setFramerateLimit(fps);
}

void GraphicsHandler::setMouseCursor(bool enabled)
{
	cursorOn = enabled;
	if (window)
		window->setMouseCursorVisible(enabled);
}

void GraphicsHandler::setVSync(bool enabled)
{
	vsync = enabled;
	if (window)
	window->setVerticalSyncEnabled(enabled);
}

void GraphicsHandler::setSize(int w, int h)
{
	width = w;
	height = h;
	defaultCamera->setSize(w, h);
	refreshCamera();
}

void GraphicsHandler::resize()
{
	if (!window)
		return;

	setSize(window->getSize().x, window->getSize().y);
}

void GraphicsHandler::setRenderSize()
{
	if (!window)
		return;

	queueCamera = 0;


	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (blackBars)
	{
		double camRatio = activeCamera->getWidth() / activeCamera->getHeight();
		double winRatio = (double)width / (double)height;
		if (camRatio > winRatio)//too wide
		{
			regionW = activeCamera->getWidth();
			regionH = regionW / winRatio;
			verBars = (regionH - activeCamera->getHeight()) / 2.0f;
			horBars = 0;
			blackBarData[3] = (GLfloat)regionW;
			blackBarData[7] = (GLfloat)verBars;
			blackBarData[9] = (GLfloat)regionW;
			blackBarData[10] = (GLfloat)verBars;
		}
		else//too tall
		{
			regionH = activeCamera->getHeight();
			regionW = regionH*winRatio;
			verBars = 0;
			horBars = (regionW - activeCamera->getWidth()) / 2.0f;
			blackBarData[3] = (GLfloat)horBars;
			blackBarData[7] = (GLfloat)regionH;
			blackBarData[9] = (GLfloat)horBars;
			blackBarData[10] = (GLfloat)regionH;
		}
		glOrtho(0, regionW, regionH, 0, _SLASK_DEPTHRANGE, -_SLASK_DEPTHRANGE);
	}
	else
	{
		glOrtho(0, activeCamera->getWidth(), activeCamera->getHeight(), 0, _SLASK_DEPTHRANGE, -_SLASK_DEPTHRANGE);
		regionW = activeCamera->getWidth();
		regionW = activeCamera->getHeight();
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


double GraphicsHandler::getCameraX()
{
	return activeCamera->x;
}
double GraphicsHandler::getCameraY()
{
	return activeCamera->y;
}
double GraphicsHandler::getCameraW()
{
	return activeCamera->getWidth();
}
double GraphicsHandler::getCameraH()
{
	return activeCamera->getHeight();
}

void GraphicsHandler::drawBegin()
{
	if (!window)
		return;

	if (queueCamera)
	setRenderSize();

	glLoadIdentity();
	if (blackBars)
		glTranslated(horBars-activeCamera->x,verBars-activeCamera->y,0);
	else
		glTranslated(-activeCamera->x,-activeCamera->y,0);
	glPushMatrix();

	window->clear();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsHandler::earlyCameraRefresh()
{
	if (queueCamera)
	setRenderSize();
}

void GraphicsHandler::drawEnd()
{
	glPopMatrix();

	if (window&&blackBars)
	{
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
		set_color(0, 0, 0, 1);
		glVertexPointer(3, GL_FLOAT, 0, blackBarData);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if (horBars<verBars)
		glTranslated(0,activeCamera->getHeight()+verBars,0);
		else
		glTranslated(activeCamera->getWidth()+horBars,0,0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		restore_color();
		glEnable(GL_TEXTURE_2D); 
		glPopMatrix();
	}

	if (!window)
		return;

	window->display();
}

void GraphicsHandler::close()
{
	if (!window)
		return;

	window->close();
	LogHandler::log("Graphics", "Window closed.");
}

void GraphicsHandler::drawText(Font *font, const char* str, double x, double y, double size, double lineSpacing, int align, double r, double g, double b, double a)
{
	if (!window)
		return;

	if (!font)
	{
		LogHandler::notify("Graphics", "Attempting to draw unloaded font.");
		return;
	}

	GLfloat lineHeight = (GLfloat)font->getLineSize();
	GLfloat yOffset = (GLfloat)font->getOffset();
	GLfloat scale = (GLfloat)size / (GLfloat)font->getSize();
	FontChar *ch;
	GLfloat d2d_tex[8] = { 0,0,1,0,0,1,1,1 };
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);

	int lines = 0;
	std::string ln(str);
	std::string *curstr = &ln;
	std::vector<std::string> linetext;
	std::vector<GLfloat> lineoffset;

	if (ln.length()==0)
	return;

	std::stringstream ss(ln);
	while (std::getline(ss, ln, '\n'))
	{
		GLfloat offset = 0;
		for (unsigned int i = 0; i < ln.size(); i++)
		{
			offset += font->getChar(ln[i])->adv;
		}
		lineoffset.push_back(offset*scale);
		linetext.push_back(ln);
		lines++;
	}

	curstr = &(linetext[0]);

	int line = 0;
	glPushMatrix();
	if (a != -1)
		set_color(r, g, b, a);
	if (lines)
		glTranslated(align == -1 ? x - lineoffset[0] : (align == 0 ? x - lineoffset[0] / 2.0f : x), y + scale*yOffset, 0);
	else
		glTranslated(x, y + scale*yOffset, 0);
	for (unsigned int i = 0; (lines||(*curstr)[i]); i++)
	{
		if ((*curstr)[i] < 0)
			continue;

		ch = font->getChar((*curstr)[i]);
		//TODO: dataSquare
		GLfloat d2d[] = { (GLfloat)ch->bw*(GLfloat)scale,-(GLfloat)ch->bh*(GLfloat)scale,drawDepth,((GLfloat)ch->bw + (GLfloat)ch->w)*(GLfloat)scale,-(GLfloat)ch->bh*(GLfloat)scale,drawDepth,(GLfloat)ch->bw*(GLfloat)scale,(-(GLfloat)ch->bh + (GLfloat)ch->h)*(GLfloat)scale,drawDepth,((GLfloat)ch->bw + (GLfloat)ch->w)*(GLfloat)scale,(-(GLfloat)ch->bh + (GLfloat)ch->h)*(GLfloat)scale,drawDepth };
		glVertexPointer(3, GL_FLOAT, 0, d2d);

		if (lines && !(*curstr)[i])
		{
			if (line < lines - 1)
			{
				glPopMatrix();
				glPushMatrix();
				line++;
				curstr = &(linetext[line]);
				i = -1;
				glTranslated(align == -1 ? x - lineoffset[line] : (align == 0 ? x - lineoffset[line] / 2.0f : x), y + yOffset*scale + line*(lineSpacing + (lineHeight)*scale), 0);
				continue;
			}
			else
				line = lines;
		}

		if (lines&&line == lines)
			break;

		glBindTexture(GL_TEXTURE_2D, ch->tex);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glTranslated(ch->adv*scale, 0, 0);
	}
	if (a != -1)
		restore_color();
	glPopMatrix();
}

void GraphicsHandler::drawSpriteExt(Sprite *sprite,double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a)
{
	if (!window)
		return;

	if (!sprite)
	{
		LogHandler::notify("Graphics", "Attempting to draw unloaded sprite.");
		return;
	}

	glPushMatrix();
	
	glTranslated(x + w / 2.0f, y + h / 2.0f, 0);
	glRotated(rot, 0, 0, 1);
	glTranslated(- w / 2.0f,- h / 2.0f, 0);
	glScaled(w,h,1);
	
	GLfloat d2d_tex[8] = { (GLfloat)fromx,(GLfloat)fromy,(GLfloat)tox,(GLfloat)fromy,(GLfloat)fromx,(GLfloat)toy,(GLfloat)tox,(GLfloat)toy };
	sprite->bind();
	if (a != -1)
		set_color(r, g, b, a);
	glVertexPointer(3, GL_FLOAT, 0, squareData);
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (a != -1)
		restore_color();
	glPopMatrix();
}

void GraphicsHandler::drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a)
{
	if (!window)
		return;

	if (!sprite)
	{
		LogHandler::notify("Graphics", "Attempting to draw unloaded sprite.");
		return;
	}

	glPushMatrix();
	double cx = (x1 + x2 + x3) / 3;
	double cy = (y1 + y2 + y3) / 3;
	GLfloat d2d[] = { (GLfloat)x1 - (GLfloat)cx,(GLfloat)y1 - (GLfloat)cy,drawDepth,(GLfloat)x2 - (GLfloat)cx,(GLfloat)y2 - (GLfloat)cy,drawDepth,(GLfloat)x3 - (GLfloat)cx,(GLfloat)y3 - (GLfloat)cy,drawDepth };
	glTranslated(cx,cy,0);
	glRotated(rot, 0, 0, 1);
	
	GLfloat d2d_tex[8] = { (GLfloat)texx1,(GLfloat)texy1,(GLfloat)texx2,(GLfloat)texy2,(GLfloat)texx3,(GLfloat)texy3 };
	sprite->bind();
	if (a != -1)
		set_color(r, g, b, a);
	glVertexPointer(3, GL_FLOAT, 0, d2d);
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	if (a != -1)
		restore_color();
	glPopMatrix();
}

void GraphicsHandler::drawRectangle(double x, double y, double w, double h, double r, double g, double b, double a)
{
	if (!window)
		return;

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);

	glTranslated(x, y, 0);
	glScaled(w, h, 1);

	set_color(r, g, b, a);

	glVertexPointer(3, GL_FLOAT, 0, squareData);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	restore_color();
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

GraphicsHandler::~GraphicsHandler()
{
	if (window)
	{
		window->close();
		delete window;
	}
	if (fontLib)
	{
		FT_Done_FreeType(*fontLib);
		delete fontLib;
	}
	delete defaultCamera;
	LogHandler::log("Graphics", "End");
}

inline void GraphicsHandler::set_color(double r, double g, double b, double a)
{
	glColor4d((GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
}

inline void GraphicsHandler::restore_color()
{
	glColor4f(1, 1, 1, 1);
}


int GraphicsHandler::getResolutions()
{
	return resolutions.size();
}

int GraphicsHandler::getResolutionWidth(unsigned int i)
{
	if (i >= resolutions.size())
	{
		std::string str = "Attempting to read supported resolution width ";
		str += std::to_string(i);
		str += "/";
		str += std::to_string(resolutions.size());
		str += " out of range.";
		LogHandler::notify("Graphics", str.c_str());
		return 0;
	}
	return resolutions[i].width;
}

int GraphicsHandler::getResolutionHeight(unsigned int i)
{
	if (i >= resolutions.size())
	{
		std::string str = "Attempting to read supported resolution height ";
		str += std::to_string(i);
		str += "/";
		str += std::to_string(resolutions.size());
		str += " out of range.";
		LogHandler::notify("Graphics", str.c_str());
		return 0;
	}
	return resolutions[i].height;
}
