#ifndef NO_STEAM

#include "../include/SteamHandler.h"
#include <iostream>

void SteamHandler::init()
{
	LogHandler::log("Steam", "Start");
	if (SteamUser())
	{
		SteamAPI_Init();

		if (SteamAPI_Init() != true)
		{
			LogHandler::error("Steam", "Initialization failed");
			return;
		}
	}
	else
	LogHandler::log("Steam", "Not in steam environment");

	LogHandler::log("Steam", "Initialized");

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

#endif