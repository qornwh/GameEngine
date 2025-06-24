#pragma once
#include "VertexArray.h"
class GameEngine;
class GameWorld;

namespace Game
{
	GameEngine& Engine();
	GameWorld* World();

	struct Cube
	{
		static VertexArray GetCubeVertex();
	};
}

