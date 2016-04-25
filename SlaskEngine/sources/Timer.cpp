#include "Timer.h"
#include <iostream>



Timer::Timer()
{
	clock = NULL;
}

void Timer::start()
{
	if (clock == NULL)
	{
		clock = new sf::Clock;
		pausedTime = 0;
		run = true;
	}
	else
		LogHandler::notify("Timer", "Already running");
}


void Timer::restart()
{
	if (clock != NULL)
	{
		stop();
		clock = new sf::Clock;
		pausedTime = 0;
		run = true;
	}
	else
		LogHandler::notify("Timer", "Doesn't Exist");
}

void Timer::unpause()
{
	if (clock == NULL)
	{
		clock = new sf::Clock;
		run = true;
	}
	else
		LogHandler::notify("Timer", "Already running");
}

void Timer::pause()
{
	if (clock != NULL)
	{
		pauseElapsed = clock->getElapsedTime();
		pausedTime += pauseElapsed.asMilliseconds();
		delete clock;
		clock = NULL;
		run = false;
	}
	else
		LogHandler::notify("Timer", "Doesn't Exist");
}

int Timer::getTime() //gives the elapsed time in milliseconds
{
	if (clock != NULL) 
	{
		elapsed = clock->getElapsedTime();

		int rt = elapsed.asMilliseconds();
		rt += pausedTime;

		return rt;
	}
	else
	{
		LogHandler::notify("Timer", "Doesn't Exist");
		return 0;
	}
}

void Timer::stop()
{
	if (clock != NULL)
	{
		delete clock;
		clock = NULL;
		run = false;
	}
	else
		LogHandler::notify("Timer", "Doesn't Exist");
}

bool Timer::isRunning()
{
	if (clock != NULL)
	{
		return run;
	}
	else
	{
		LogHandler::notify("Timer", "Doesn't Exist");
		return false;
	}
}

Timer::~Timer()
{
	if (clock != NULL)
	{
		delete clock;
		clock = NULL;
	}
}