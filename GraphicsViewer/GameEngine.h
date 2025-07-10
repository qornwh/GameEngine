#pragma once
#include "Singleton.h"
#include <vector>

struct GLFWwindow;
class GameWorld;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

class GameEngine : public Singleton<GameEngine>
{
public:
	GameEngine();
	~GameEngine();

	void Init();
	void OpenWorld();
	void Loop();

	GameWorld* GetWorld() { return world_; }
	GLFWwindow* GetWindow() { return window_; }
private:
	GLFWwindow* window_;
	GameWorld* world_;
};

