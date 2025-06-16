#pragma once
#include<memory>

class Actor;

class ImGuiActor : public std::enable_shared_from_this<ImGuiActor>
{
public:
	ImGuiActor();
	~ImGuiActor();

	void Draw();

	void SetActor(Actor* actor);
	Actor* GetActor() { return actor_; }
private:
	Actor* actor_;
};

