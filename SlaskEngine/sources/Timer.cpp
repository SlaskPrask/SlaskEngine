#include "Timer.h"
#include <iostream>



Timer::Timer()
{
	clock = NULL;
}

void Timer::startTimer()
{
	if (clock == NULL)
	{
		clock = new sf::Clock;
		pausedTime = 0;
		run = true;
	}
	else
		LogHandler::error("Timer", "Already running");
}

void Timer::unpauseTimer()
{
	if (clock == NULL)
	{
		clock = new sf::Clock;
		run = true;
	}
	else
		LogHandler::error("Timer", "Already running");
}

void Timer::pauseTimer()
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
		LogHandler::error("Timer", "Doesn't Exist");
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
		LogHandler::error("Timer", "Doesn't Exist");
		return 0;
	}
}

void Timer::stopTimer()
{
	if (clock != NULL)
	{
		delete clock;
		clock = NULL;
		run = false;
	}
	else
		LogHandler::error("Timer", "Doesn't Exist");
}

bool Timer::isTimerRunning()
{
	if (clock != NULL)
	{
		return run;
	}
	else
	{
		LogHandler::error("Timer", "Doesn't Exist");
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