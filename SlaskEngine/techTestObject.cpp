#include "techTestObject.h"

using namespace slask;

TestObject::TestObject()
{
	position = 0;
	sprite = getSprite(0, 0);

	/*testF=new Font("Progandae.otf");
	TestMB=new AudioBank("fmod/TestBank/Build/Desktop/Master Bank.bank");
	TestMSB=new AudioBank("fmod/TestBank/Build/Desktop/Master Bank.strings.bank");
	getSound(1,0)=new Audio("Music");
	getSound(1,1)=new Audio("Audio");*/

	/*File file;

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
	file.copySave(2, 5, "Saves/", "SAVE", "txt", "Slask");*/

	depth(-10);
}

void TestObject::run()
{
	windowHeight = getWindowHeight();
	windowWidth = getWindowWidth();

	position += 3;
	if (position > 360)
		position -= 360;

	if (getKeyPress(Key::Num1))
	{
		playSound(getSound(1, 0));
	}
	if (getKeyPress(Key::Q))
	{
		stopSound(getSound(1, 0));
	}
	if (getKeyPress(Key::A))
	{
		pauseSound(getSound(1, 0));
	}
	if (getKeyPress(Key::Z))
	{
		unpauseSound(getSound(1, 0));
	}
	if (getKeyPress(Key::Num2))
	{
		playSound(getSound(1, 1));
	}
	if (getKeyPress(Key::W))
	{
		stopSound(getSound(1, 1));
	}
	if (getKeyPress(Key::S))
	{
		pauseSound(getSound(1, 1));
	}
	if (getKeyPress(Key::X))
	{
		unpauseSound(getSound(1, 1));
	}
	if (getKeyPress(Key::Num3))
	{
		setSoundPitch(getSound(1, 1), 2);
		setSoundPitch(getSound(1, 0), 2);
	}
	if (getKeyPress(Key::Num4))
	{
		setSoundPitch(getSound(1, 1), 0.5f);
		setSoundPitch(getSound(1, 0), 0.5f);
	}
	if (getKeyPress(Key::Num5))
	{
		setSoundPitch(getSound(1, 1), 1);
		setSoundPitch(getSound(1, 0), 1);
	}
	if (getKeyPress(Key::Num0))
	{
		//OH YEAH
		setSoundTimePosition(getSound(1, 0), 37678);
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

	if (getKeyPress(Key::Pause))//pause first half of objects
	{
		if (taggy->runs())
			taggy->disableRun();
		else
			taggy->enableRun();
	}
	if (taggy2 != NULL)
	{
		if (getKeyPress(Key::P))//pause 2nd half of objects
		{
			if (taggy2->runs())
				taggy2->disableRun();
			else
				taggy2->enableRun();
		}
		if (getKeyPress(Key::O))//don't draw 2nd half of objects
		{
			if (taggy2->draws())
				taggy2->disableDraw();
			else
				taggy2->enableDraw();
		}
		if (getKeyPress(Key::N))//delete 2nd half of object tag handling (should unpause and keep objects)
		{
			delete taggy2;
			taggy2 = NULL;
		}
	}

	if (getKeyPress(Key::S))
		depth(depth() + 100);
}

void TestObject::draw()
{
	drawText(getFont(0, 0), "I'm Slask\nI'm Slask\nI'm Slask\nKappa", getCameraX() + 5, getCameraY() + 5, 14,2, 1, 1, 1, 1);
}

TestObject::~TestObject()
{
}
