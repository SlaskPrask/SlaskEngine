#include "SteamHandler.h"
#include <iostream>


SteamHandler* SteamHandler::instance()
{
	static SteamHandler steamhandler;
	return &steamhandler;
}

void SteamHandler::init()
{
	if (SteamUser())
	{
		LogHandler::log("Steam", "Start");
		SteamAPI_Init();

		if (SteamAPI_Init() != true)
		{
			LogHandler::error("Steam", "Initialization failed");
			return;
		}

		LogHandler::log("Steam", "Initialized");
	}
	else
		LogHandler::log("Steam", "Not in steam environment");

}

std::string SteamHandler::getUserName()
{
	if (!SteamUser())
		return "Slask";
	else
		return SteamFriends()->GetPersonaName();
}



SteamHandler::~SteamHandler()
{
	if (SteamUser())
		SteamAPI_Shutdown();
}
