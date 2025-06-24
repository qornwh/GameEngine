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
	MeshComponent* mesh_comp_;

	// 등속 원운동 1초에 90
	float angle_ = 1.f;
};

