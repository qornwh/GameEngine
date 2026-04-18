#pragma once
#include "Singleton.h"
#include <vector>

struct GLFWwindow;
class GameWorld;

constexpr int DefaultWindowWidth = 1024;
constexpr int DefaultWindowHeight = 720;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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

	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }
	float GetAspect() const { return (height_ > 0) ? static_cast<float>(width_) / static_cast<float>(height_) : 1.f; }
	void SetSize(int w, int h) { width_ = w; height_ = h; }
private:
	GLFWwindow* window_;
	GameWorld* world_;
	int width_ = DefaultWindowWidth;
	int height_ = DefaultWindowHeight;
};

