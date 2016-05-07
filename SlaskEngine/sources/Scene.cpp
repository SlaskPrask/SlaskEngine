#include "../include/Scene.h"
#include "../include/SlaskEngine.h"

Scene::Scene()
{
	width = height = 1;
	SlaskEngine::instance()->switchScene(this);
}

void Scene::_deleteObjects()
{
	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		(*it)->_scene = NULL;
		(*it)->_persistent = 1;
		(*it)->destroy();
	}
}

unsigned int Scene::id()
{
	return 0;
}

Scene::~Scene()
{
	_deleteObjects();
}

void Scene::run()
{
}
