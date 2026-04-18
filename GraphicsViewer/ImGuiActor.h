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
	void SetActor2(Actor* actor2);
	Actor* GetActor() { return actor_; }
	Actor* GetActor2() { return actor2_; }
private:
	Actor* actor_;
	Actor* actor2_;
};

