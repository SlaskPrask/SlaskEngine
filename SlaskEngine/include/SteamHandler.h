#pragma once

#ifndef NO_STEAM

#include <steam_api.h>
//#include <steam_gameserver.h>

#include "../include/LogHandler.h"

class SteamHandler
{
private:

	

public:
	static SteamHandler* instance();
	void init();

	std::string getUserName();
	~SteamHandler();
};


#endif
