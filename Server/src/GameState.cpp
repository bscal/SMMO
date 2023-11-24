#include "GameState.h"

#include "Lib/Jobs.h"

internal void GameRun();
internal void GameShutdown();

int
GameInitialize()
{
	size_t permanentMemorySize = Megabytes(16);
	size_t gameMemorySize = Megabytes(16);
	size_t frameMemorySize = Megabytes(16);
	size_t totalMemory = permanentMemorySize + gameMemorySize + frameMemorySize;
	zpl_virtual_memory vm = zpl_vm_alloc(0, totalMemory);
	
	uintptr_t memoryOffset = (uintptr_t)vm.data;

	ArenaCreate(&State.GameArena, (void*)memoryOffset, permanentMemorySize);
	memoryOffset += permanentMemorySize;

	GeneralPurposeCreate(&State.GeneralPurposeMemory, (void*)memoryOffset, gameMemorySize);
	memoryOffset += gameMemorySize;

	ArenaCreate(&TransientState.TransientArena, (void*)memoryOffset, frameMemorySize);
	memoryOffset += frameMemorySize;

	SAssert(memoryOffset - vm.size == (size_t)vm.data);

	InitializeMemoryTracking();

	ArenaSnapshot tempMemoryInit = ArenaSnapshotBegin(&TransientState.TransientArena);

	PushMemoryIgnoreFree();

	JobsInitialize(7);

	ArenaSnapshotEnd(tempMemoryInit);

	GameRun();

	GameShutdown();

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