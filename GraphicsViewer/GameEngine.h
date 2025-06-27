#pragma once
#include "Singleton.h"
#include <vector>

struct GLFWwindow;
class GameWorld;

class GameEngine : public Singleton<GameEngine>
{
public:
	GameEngine();
	~GameEngine();

	void Init();
	void OpenWorld();
	void Loop();

	GameWorld* GetWorld() { return world_; }
private:
	GLFWwindow* window_;
	GameWorld* world_;
};

