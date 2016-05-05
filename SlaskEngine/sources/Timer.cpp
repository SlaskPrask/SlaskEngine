#include "../include/Timer.h"
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
	LogHandler::notify("Timer", "Timer is already running.");
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
		start();
}

void Timer::unpause()
{
	if (clock == NULL)
	{
		clock = new sf::Clock;
		run = true;
	}
	else
		start();
}

void Timer::pause()
{
	if (clock != NULL && run == true)
	{
		pauseElapsed = clock->getElapsedTime();
		pausedTime += pauseElapsed.asMilliseconds();
		delete clock;
		clock = NULL;
		run = false;
	}
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
}

bool Timer::isRunning()
{
	if (clock != NULL)
	{
		return run;
	}
	else
	{
		return false;
	}
}

Timer::~Timer()
{
	if (clock != NULL)
	delete clock;
}