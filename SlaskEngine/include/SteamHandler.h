#pragma once

#ifndef NO_STEAM

#include <steam_api.h>
//#include <steam_gameserver.h>

#include "LogHandler.h"

class SteamHandler
{
private:

	

public:
	inline static SteamHandler* instance()
	{
		static SteamHandler steamhandler;
		return &steamhandler;
	}
	void init();

	std::string getUserName();
	~SteamHandler();
};


#endif
