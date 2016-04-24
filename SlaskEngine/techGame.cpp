#include "sources/Slask.h"

#include "techTestObject.h"
#include "techPlayer.h"

using namespace slask;

void slask::start()
{
	setTitle("SlaskEngine Tech Demo");
	setWindowed(1280, 720);

	createObject(new TestObject());
	createObject(new player());
}

void slask::end()
{
	log("WindowCLosed");
	exitGame();
}
