#include "GameGlobals.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "ActorFactory.h"

GameEngine& Game::Engine()
{
	return GameEngine::GetInstance();
}

GameWorld* Game::World()
{
	return GameEngine::GetInstance().GetWorld();
}

ActorFactory* Game::AFactory()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return GameEngine::GetInstance().GetWorld()->GetActorFactory();
}

VertexArray Game::Cube::GetCubeVertex()
{
	static std::vector<Vertex> vertexs = {
		// Front face
		{{-1, -1,  1}, { 0,  0,  1}, {0, 0}},
		{{ 1, -1,  1}, { 0,  0,  1}, {1, 0}},
		{{ 1,  1,  1}, { 0,  0,  1}, {1, 1}},
		{{-1,  1,  1}, { 0,  0,  1}, {0, 1}},

		// Back face
		{{ 1, -1, -1}, { 0,  0, -1}, {0, 0}},
		{{-1, -1, -1}, { 0,  0, -1}, {1, 0}},
		{{-1,  1, -1}, { 0,  0, -1}, {1, 1}},
		{{ 1,  1, -1}, { 0,  0, -1}, {0, 1}},

		// Left face
		{{-1, -1, -1}, {-1,  0,  0}, {0, 0}},
		{{-1, -1,  1}, {-1,  0,  0}, {1, 0}},
		{{-1,  1,  1}, {-1,  0,  0}, {1, 1}},
		{{-1,  1, -1}, {-1,  0,  0}, {0, 1}},

		// Right face
		{{ 1, -1,  1}, { 1,  0,  0}, {0, 0}},
		{{ 1, -1, -1}, { 1,  0,  0}, {1, 0}},
		{{ 1,  1, -1}, { 1,  0,  0}, {1, 1}},
		{{ 1,  1,  1}, { 1,  0,  0}, {0, 1}},

		// Top face
		{{-1,  1,  1}, { 0,  1,  0}, {0, 0}},
		{{ 1,  1,  1}, { 0,  1,  0}, {1, 0}},
		{{ 1,  1, -1}, { 0,  1,  0}, {1, 1}},
		{{-1,  1, -1}, { 0,  1,  0}, {0, 1}},

		// Bottom face
		{{-1, -1, -1}, { 0, -1,  0}, {0, 0}},
		{{ 1, -1, -1}, { 0, -1,  0}, {1, 0}},
		{{ 1, -1,  1}, { 0, -1,  0}, {1, 1}},
		{{-1, -1,  1}, { 0, -1,  0}, {0, 1}},
	};

	static unsigned int cubeIndices[] = {
		// Front face
		0, 1, 2,  2, 3, 0,
		// Back face
		4, 5, 6,  6, 7, 4,
		// Left face
		8, 9,10, 10,11, 8,
		// Right face
		12,13,14, 14,15,12,
		// Top face
		16,17,18, 18,19,16,
		// Bottom face
		20,21,22, 22,23,20
	};

	static VertexArray vao(vertexs, static_cast<unsigned int>(vertexs.size()), cubeIndices, 24);
	return vao;
}
