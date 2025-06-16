#include "GameGlobals.h"
#include "GameEngine.h"
#include "GameWorld.h"

GameEngine& Game::Engine()
{
	return GameEngine::GetInstance();
}

GameWorld* Game::World()
{
	return GameEngine::GetInstance().GetWorld();
}
