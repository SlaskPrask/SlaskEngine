#include "../include/EngineNamespace.h"
#include "../include/SlaskEngine.h"

bool _engine::isObjectDestroyed(Object* o)
{
	return SlaskEngine::instance()->isObjectDestroyed(o);
}