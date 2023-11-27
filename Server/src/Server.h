#pragma once

#include "Core.h"

#include "GameState.h"

struct Server
{

};

int 
ServerInitialize()
{
	GameInitialize();

	return 0;
}

void ServerRun();

void ServerShutdown();
