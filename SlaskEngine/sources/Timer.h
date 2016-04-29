#include <SFML/System.hpp>
#include "LogHandler.h"
#pragma once

class Timer //undocced
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

	void start();
	void unpause();
	int getTime();
	bool isRunning();
	void stop();
	void restart();
	void pause();


};