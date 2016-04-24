#include <SFML/Main.hpp>
#include "LogHandler.h"
#pragma once

class Timer
{
private:

	sf::Time elapsed;
	sf::Clock* clock;
	sf::Time pauseElapsed;
	int pausedTime;
	bool run;


public:
	Timer();
	~Timer();

	void startTimer();
	void unpauseTimer();
	int getTime();
	bool isTimerRunning();
	void stopTimer();
	void pauseTimer();


};