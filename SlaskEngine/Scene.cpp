#include "Scene.h"



Scene::Scene()
{
	w = h = 0;
	block = 0;
}

void Scene::load(const char* file)
{
	w = 100;
	h = 50;
	block = new int*[w];
	for (int i = 0; i<w; i++)
	{
		block[i] = new int[h];
		for (int j = 0; j<h; j++)
			block[i][j] = (i == 0 || j == 0 || j == h - 1 || i == w - 1) ? Wall : Empty;
	}
}

Scene::~Scene()
{
}
