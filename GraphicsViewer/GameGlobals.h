#pragma once
#include "VertexArray.h"

class GameEngine;
class GameWorld;
class ActorFactory;

namespace Game
{
	GameEngine& Engine();
	GameWorld* World();
	ActorFactory* AFactory();

	struct Cube
	{
		static VertexArray GetCubeVertex();
	};
}

