#pragma once

#include "Core.h"

#include "GameState.h"

#include <ogre/sdk/include/OGRE/Ogre.h>
#include <ogre/sdk/include/OGRE/Bites/OgreApplicationContext.h>
#include <ogre/sdk/include/OGRE/Bites/OgreInput.h>
#include <ogre/sdk/include/OGRE/RTShaderSystem/OgreRTShaderSystem.h>

struct ManagedState
{
	Ogre::Vector2f SomeVec;

	ManagedState()
		: SomeVec()
	{
	}

};

struct ManagedServer : public Ogre::ApplicationContext, public Ogre::InputListener
{

};

struct Server
{

};

int 
ServerInitialize()
{
	GameInitialize();

	ManagedState* state = new ManagedState();

	return 0;
}

void ServerRun();

void ServerShutdown();
