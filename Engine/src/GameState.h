#pragma once

#include "Core.h"

#include "Structures/SList.h"
#include "Structures/ArrayList.h"
#include "Structures/HashMap.h"

#include "Lib/Arena.h"
#include "Lib/LinearArena.h"
#include "Lib/GeneralAllocator.h"
#include "Lib/Jobs.h"

struct GameState
{
	Arena GameArena;
	GeneralPurposeAllocator GeneralPurposeMemory;

	bool IsGamePaused;
};

struct TransientGameState
{
	Arena TransientArena;
};

global_var struct GameState State;
global_var struct TransientGameState TransientState;

#define DeltaTime GetFrameTime()

#define GetGameState() (&State)

SAPI int GameInitialize();
SAPI void GameRun();
SAPI void GameShutdown();
