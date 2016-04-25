#include "techTestObject.h"

using namespace slask;

TestObject::TestObject()
{
	windowHeight = getWindowHeight();
	windowWidth = getWindowWidth();
	position = 0;
	sprite = getSprite(0, 0);

	testF=new Font("Progandae.otf");
	TestMB=new AudioBank("fmod/TestBank/Build/Desktop/Master Bank.bank");
	TestMSB=new AudioBank("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	Team10=new Audio("Music");
	Guitar=new Audio("Audio");

	File file;

	file.add("Hi");
	file.add("Zas");
	file.add(19123);
	file.add("I'm Slask");
	file.save("Save Test.txt", true);

	file.load("Save Test.txt", true);
	file.set(1, "Slask");
	file.set(2, 12);
	std::cout << file.get(0) << '\n';
	std::cout << file.get(1) << '\n';
	std::cout << file.getint(2) << '\n';
	std::cout << file.get(3) << '\n';

	file.searchFile(&files, "Saves/", "*.txt");
	//file.compare(&files, "TestCompare.txt");

	file.deleteSave(5, "Saves/", "SAVE", "txt", "Slask");
	file.deleteSave(3, "Saves/", "SAVE", "txt", "Zas");
	file.checkSaves(&files, 5, "Saves/", "SAVE", "txt");
	file.newSave(3, "Saves/", "SAVE", "txt", "Zas");
	file.copySave(2, 5, "Saves/", "SAVE", "txt", "Slask");
}

void TestObject::run()
{
	windowHeight = getWindowHeight();
	windowWidth = getWindowWidth();

	position += 3;
	if (position>360)
	position -= 360;

	if (getKeyPress(Key::Num1))
	{
		playSound(Team10);
	}
	if (getKeyPress(Key::Q))
	{
		stopSound(Team10);
	}
	if (getKeyPress(Key::A))
	{
		pauseSound(Team10);
	}
	if (getKeyPress(Key::Z))
	{
		unpauseSound(Team10);
	}
	if (getKeyPress(Key::Num2))
	{
		playSound(Guitar);
	}
	if (getKeyPress(Key::W))
	{
		stopSound(Guitar);
	}
	if (getKeyPress(Key::S))
	{
		pauseSound(Guitar);
	}
	if (getKeyPress(Key::X))
	{
		unpauseSound(Guitar);
	}
	if (getKeyPress(Key::Num3))
	{
		setSoundPitch(Guitar, 2);
		setSoundPitch(Team10, 2);
	}
	if (getKeyPress(Key::Num4))
	{
		setSoundPitch(Guitar, 0.5f);
		setSoundPitch(Team10, 0.5f);
	}
	if (getKeyPress(Key::Num5))
	{
		setSoundPitch(Guitar, 1);
		setSoundPitch(Team10, 1);
	}
	if (getKeyPress(Key::Num0))
	{
		//OH YEAH
		setSoundTimePosition(Team10, 37678);
	}


	if (getKeyPress(Key::LShift) && getKeyPress(Key::Z))
	{
		setFullscreenWindowed(1920, 1080);
	}
	if (getKeyPress(Key::LShift) && getKeyPress(Key::X))
	{
		setWindowed(1280, 720);
	}
	if (getKeyPress(Key::LShift) && getKeyPress(Key::C))
	{
		setWindowed(800, 600);
	}
	if (getKeyPress(Key::LShift) && getKeyPress(Key::V))
	{
		setFullscreen(1920, 1080);
	}
}

void TestObject::draw()
{
	//the big at the back, stretched
	drawSprite(sprite, 10, 10, windowWidth - 20, windowHeight - 20, 1000);
	//small not moving, static position
	drawSprite(sprite, 100, 100, 1);
	//rolling one, static position
	drawSprite(sprite, 100 + cos(position*3.14159265 / 180.0f) * 100, 100 + sin(position*3.14159265 / 180.0f) * 100, 10);
	//spinning whole, static position
	drawSpriteRot(sprite, 300, 150, 100, 100, position, -10);
	//spinning red, static position
	drawSpriteExt(sprite, 150, 400, 200, 100, 0, 0, .5, .5, -position, 1, 0, 0, 0.5, -20);
	//top left, dynamic position
	drawSpritePoly(sprite, 0, 0, 100, 0, 0, 100, .5, 0, 0, 1, 1, 1, -100);
	//top right, dynamic position
	drawSpritePoly(sprite, windowWidth, 0, windowWidth, 100, windowWidth - 100, 0, .5, 0, 0, 1, 1, 1, -100);
	//bottom left, dynamic position
	drawSpritePoly(sprite, 0, windowHeight, 0, windowHeight - 100, 100, windowHeight, .5, 0, 0, 1, 1, 1, -100);
	//bottom right, dynamic position
	drawSpritePoly(sprite, windowWidth, windowHeight, windowWidth - 100, windowHeight, windowWidth, windowHeight - 100, .5, 0, 0, 1, 1, 1, -100);
	//spinning green, static position
	drawSpritePolyExt(sprite, 300, 200, 200, 400, 400, 400, .5, 0, 0, 1, 1, 1, position*2.0f, 0, 1, 0, 1, -100);
}

TestObject::~TestObject()
{
}
