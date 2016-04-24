#include <steam_api.h>
//#include <steam_gameserver.h>
#include "LogHandler.h"


#pragma once
class SteamHandler
{
private:

	

public:
	static SteamHandler* instance();
	void init();

	std::string getUserName();
	~SteamHandler();
};

