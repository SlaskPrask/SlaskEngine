#include "../include/Scene.h"
#include "../include/SlaskEngine.h"

Scene::Scene()
{
	width = height = 1;
	_deathMark = 0;
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
		LogHandler::error("Engine", "delete called on a Scene. Do not delete scenes, to switch to a new one simply create a new instance.");

	_deleteObjects();
}

void Scene::run()
{
}
