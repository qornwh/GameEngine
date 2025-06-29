#pragma once
#include "GameWorld.h"

class ImGuiActor;

class TestGameWorld : public GameWorld
{
public:
	void Start();
	std::shared_ptr<ImGuiActor> GetImGuiActor() { return imgui_actor_ptr_; }

protected:
	void AfterUpdate();

	float lastX = (float)1024 / 2.0;
	float lastY = (float)720 / 2.0;
	bool firstMouse = true;

private:
	std::shared_ptr<ImGuiActor> imgui_actor_ptr_;
};

