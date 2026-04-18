#pragma once
#include "Actor.h"

class MeshComponent;

class TestActor : public Actor
{
public:
	TestActor();
	~TestActor();

	void Start() override;
	void Update(float deltaTime) override;

private:
	MeshComponent* character_comp_;

	// 등속 원운동 1초에 90
	float angle_ = 1.f;
	float cur_angle_ = 0;
};

class FloorActor : public Actor
{
public:
	void Start() override;

private:
	MeshComponent* floor_comp_;
};

