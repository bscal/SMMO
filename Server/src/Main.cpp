#include "Engine.h"

#include "Server.h"

int
main(int argCount, char** args)
{
	EngineStartup();
	ServerInitialize();

	return 0;
}

