#include "GraphicsHandler.h"

GraphicsHandler* GraphicsHandler::instance()
{
	static GraphicsHandler graphicshandler;
	return &graphicshandler;
}

void GraphicsHandler::init(int w, int h, const char* title)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Default, settings);
	setTitle(title);
	setVSync(true);
	setFPS(60);
	setSize(w, h);
	setRenderSize(w, h);

	window->setActive();
	
	glEnable(GL_DEPTH_TEST);
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
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//todo drawing nice with culling maybe?
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void GraphicsHandler::setTitle(const char* title)
{
	label = title;
	window->setTitle(title);
}

void GraphicsHandler::setFPS(int fps)
{
	framespersecond = fps;
	window->setFramerateLimit(fps);
}

void GraphicsHandler::setVSync(bool enabled)
{
	vsync = enabled;
	window->setVerticalSyncEnabled(enabled);
}

void GraphicsHandler::setSize(int w, int h)
{
	width = w;
	height = h;
}

void GraphicsHandler::resize()
{
	setSize(window->getSize().x, window->getSize().y);
	setRenderSize(window->getSize().x, window->getSize().y);
}

void GraphicsHandler::setRenderSize(int w, int h) 
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w,h, 0, DEPTHRANGE, -DEPTHRANGE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int GraphicsHandler::getWidth()
{
	return width;
}

int GraphicsHandler::getHeight()
{
	return height;
}

int GraphicsHandler::getFPS()
{
	return framespersecond;
}

bool GraphicsHandler::getVSync()
{
	return vsync;
}

const char* GraphicsHandler::getTitle()
{
	return label;
}

sf::RenderWindow* GraphicsHandler::getWindow()
{
	return window;
}

void GraphicsHandler::drawBegin()
{
	window->clear();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsHandler::drawEnd()
{
	window->display();
}

void GraphicsHandler::close()
{
	window->close();
}

void GraphicsHandler::drawSprite(Sprite* sprite, double x, double y, double depth)
{
	drawSpriteExt(sprite, x, y, sprite->getWidth(), sprite->getHeight(), 0, 0, 1, 1, 0, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSprite(Sprite* sprite,double x, double y,double w, double h, double depth)
{
	drawSpriteExt(sprite, x, y, w, h, 0, 0, 1, 1, 0, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSpritePart(Sprite* sprite, double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double depth)
{
	drawSpriteExt(sprite, x, y, w, h, fromx, fromy, tox, toy, 0, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSpriteRot(Sprite* sprite, double x, double y, double w, double h, double rot, double depth)
{
	drawSpriteExt(sprite, x, y, w, h, 0, 0, 1, 1, rot, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSpritePoly(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double depth)
{
	drawSpritePolyExt(sprite, x1, y1, x2, y2, x3, y3, texx1, texy1, texx2, texy2, texx3, texy3, 0, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSpritePolyRot(Sprite* sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double depth)
{
	drawSpritePolyExt(sprite, x1, y1, x2, y2, x3, y3, texx1, texy1, texx2, texy2, texx3, texy3, rot, 1, 1, 1, -1, depth);
}

void GraphicsHandler::drawSpriteExt(Sprite *sprite,double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a, double depth)
{
	glPushMatrix();
	GLfloat d2d[] = { -w/2.0f, - h/2.0f,depth, + w/2.0f, - h / 2.0f,depth, - w / 2.0f, + h / 2.0f,depth, + w / 2.0f, + h / 2.0f,depth };

	glTranslated(x+w/2.0f, y + h / 2.0f, 0);
	glRotated(rot, 0, 0, 1);
	GLfloat d2d_tex[8] = { fromx,fromy,tox,fromy,fromx,toy,tox,toy };
	sprite->bind();
	if (a != -1)
		set_color(r, g, b, a);
	glVertexPointer(3, GL_FLOAT, 0, d2d);
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (a != -1)
		restore_color();
	glPopMatrix();
}

void GraphicsHandler::drawSpritePolyExt(Sprite *sprite, double x1, double y1, double x2, double y2, double x3, double y3, double texx1, double texy1, double texx2, double texy2, double texx3, double texy3, double rot, double r, double g, double b, double a, double depth)
{
	glPushMatrix();
	double cx = (x1 + x2 + x3) / 3;
	double cy = (y1 + y2 + y3) / 3;
	GLfloat d2d[] = { x1 - cx,y1 - cy,depth,x2 - cx,y2 - cy,depth,x3 - cx,y3 - cy,depth };
	glTranslated(cx,cy,0);
	glRotated(rot, 0, 0, 1);
	
	GLfloat d2d_tex[8] = { texx1,texy1,texx2,texy2,texx3,texy3 };
	sprite->bind();
	if (a != -1)
		set_color(r, g, b, a);
	glVertexPointer(3, GL_FLOAT, 0, d2d);
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (a != -1)
		restore_color();
	glPopMatrix();
	/*
	GLfloat d2d[] = { x1,y1,depth,x2,y2,depth,x3,y3,depth };
	if (rot)
	{
		double w = max(abs(x1 - x2), max(abs(x2 - x3), abs(x1 - x3)));
		double h = max(abs(y1 - y2), max(abs(y2 - y3), abs(y1 - y3)));
		d2d[0] += w / 2 + cos(rad(rot + 180.0f))*w / 2 + cos(rad(rot + 90.0f))*h / 2;
		d2d[1] += h / 2 - sin(rad(rot + 180.0f))*w / 2 - sin(rad(rot + 90.0f))*h / 2;
		d2d[2] += -w / 2 + cos(rad(rot))*w / 2 + cos(rad(rot + 90.0f))*h / 2;
		d2d[3] += h / 2 - sin(rad(rot))*w / 2 - sin(rad(rot + 90.0f))*h / 2;
		d2d[4] += w / 2 + cos(rad(rot + 180.0f))*w / 2 + cos(rad(rot - 90.0f))*h / 2;
		d2d[5] += -h / 2 - sin(rad(rot + 180.0f))*w / 2 - sin(rad(rot - 90.0f))*h / 2;
	}
	GLfloat d2d_tex[8] = { texx1,texy1,texx2,texy2,texx3,texy3 };
	sprite->bind();
	if (a != -1)
		set_color(r, g, b, a);
	glVertexPointer(3, GL_FLOAT, 0, d2d);
	glTexCoordPointer(2, GL_FLOAT, 0, d2d_tex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (a != -1)
		restore_color();
	*/
}

GraphicsHandler::~GraphicsHandler()
{
	delete window;
}

inline void GraphicsHandler::set_color(double r, double g, double b, double a)
{
	glColor4f(r, g, b, a);
}

inline void GraphicsHandler::restore_color()
{
	glColor4f(1, 1, 1, 1);
}