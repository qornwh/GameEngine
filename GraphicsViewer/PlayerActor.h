#pragma once
#include "Actor.h"
#include <GLFW/glfw3.h>

class PlayerActor : public Actor
{
public:
	PlayerActor();
	~PlayerActor();

	void Start() override;
	void Update(float deltaTime) override;
	void SetCamera(class CameraActor* camera);

	void CameraMove();

private:
	bool isFirst = false;
	float last_pos_x_ = 0;
	float last_pos_y_ = 0;
	float sensitivity_ = 0.05f;

	class MovementComponent* moveComp_;
	class CameraActor* camera_;
};

