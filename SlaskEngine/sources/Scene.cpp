#include "../include/Scene.h"
#include "../include/SlaskEngine.h"

Scene::Scene()
{
	width = height = 1;
	_deathMark = 0;
	_deleted=0;
	SlaskEngine::instance()->switchScene(this);
}

void Scene::_deleteObjects()
{
	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		SlaskEngine::instance()->forcePersistent(*it);
		(*it)->destroy();
	}
}

unsigned int Scene::id()
{
	return 0;
}

Scene::~Scene()
{
	if (!_deathMark)
	{
		std::ostringstream s;
		s << "delete called on an Scene[";
		s << this;
		s << "].  Do not delete scenes, to switch to a new one simply create a new instance.";
		LogHandler::error("Engine",s.str().c_str());
	}
	_deleted=1;

	_deleteObjects();
}

void Scene::run()
{
}
