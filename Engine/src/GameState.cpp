#include "GameState.h"

int
GameInitialize()
{
	SPrint("Hello");

	return 0;
}

void
GameRun()
{
	while (1)
	{
		ArenaSnapshot tempMemory = ArenaSnapshotBegin(&TransientState.TransientArena);

		ArenaSnapshotEnd(tempMemory);
	}
}


void GameLateUpdate()
{
}


void
GameShutdown()
{
	ShutdownMemoryTracking();
}