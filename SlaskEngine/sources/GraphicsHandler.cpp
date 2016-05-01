#include "GraphicsHandler.h"
#include "Camera.h"

//TODO: window checks

GraphicsHandler* GraphicsHandler::instance()
{
	static GraphicsHandler graphicshandler;
	return &graphicshandler;
}

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
	framespersecond = 60;
	vsync = true;
	label = title;
	width = height = 0;

	LogHandler::log("Graphics", "Initialized");
}

void GraphicsHandler::initGL()
{
	if (!window)
		return;

	setVSync(vsync);
	setFPS(framespersecond);

	window->setActive();

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
	if (cam == NULL)
		activeCamera = defaultCamera;
	else
		activeCamera = cam;
}

bool GraphicsHandler::setFullscreen(int w, int h)
{
	close();

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
	if (activeCamera == defaultCamera)
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
	queueCamera = 0;

	glViewport(0, 0, width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, activeCamera->getWidth(), activeCamera->getHeight(), 0, DEPTHRANGE, -DEPTHRANGE);
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

double GraphicsHandler::getCameraX()
{
	return activeCamera->getX();
}

double GraphicsHandler::getCameraY()
{
	return activeCamera->getY();
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
	glLoadIdentity();
	glTranslated(-activeCamera->getX(), -activeCamera->getY(), 0);
	glPushMatrix();

	if (!window)
		return;

	if (queueCamera)
	setRenderSize();

	window->clear();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsHandler::drawEnd()
{
	glPopMatrix();

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

void GraphicsHandler::drawSpriteExt(Sprite *sprite,double x, double y, double w, double h, double fromx, double fromy, double tox, double toy, double rot, double r, double g, double b, double a, double depth)
{
	if (!window)
		return;

	if (!sprite)
	{
		LogHandler::notify("Graphics", "Attempting to draw unloaded sprite.");
		return;
	}

	glPushMatrix();
	GLfloat d2d[] = { -(GLfloat)w/2.0f, -(GLfloat)h/2.0f,(GLfloat)depth, +(GLfloat)w/2.0f, -(GLfloat)h/2.0f,(GLfloat)depth, -(GLfloat)w/2.0f, +(GLfloat)h / 2.0f,(GLfloat)depth, +(GLfloat)w / 2.0f, (GLfloat)h / 2.0f,(GLfloat)depth };

	glTranslated(x+w/2.0f, y + h / 2.0f, 0);
	glRotated(rot, 0, 0, 1);
	GLfloat d2d_tex[8] = { (GLfloat)fromx,(GLfloat)fromy,(GLfloat)tox,(GLfloat)fromy,(GLfloat)fromx,(GLfloat)toy,(GLfloat)tox,(GLfloat)toy };
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
	GLfloat d2d[] = { (GLfloat)x1 - (GLfloat)cx,(GLfloat)y1 - (GLfloat)cy,(GLfloat)depth,(GLfloat)x2 - (GLfloat)cx,(GLfloat)y2 - (GLfloat)cy,(GLfloat)depth,(GLfloat)x3 - (GLfloat)cx,(GLfloat)y3 - (GLfloat)cy,(GLfloat)depth };
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

GraphicsHandler::~GraphicsHandler()
{
	if (window)
	{
		window->close();
		delete window;
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

int GraphicsHandler::getResolutionWidth(int i)
{
	return resolutions[i].width;
}

int GraphicsHandler::getResolutionHeight(int i)
{
	return resolutions[i].height;
}
