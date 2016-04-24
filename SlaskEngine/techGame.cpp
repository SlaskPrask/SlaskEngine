#include "sources/Slask.h"

#include "techTestObject.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	createObject(new TestObject());
}

void slask::end()
{
	log("WindowCLosed");
	exitGame();
}
