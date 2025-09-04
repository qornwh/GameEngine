#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class MovementComponent : public Component
{
public:
	MovementComponent(Actor* actor);
	~MovementComponent();

	void Update(float deltaTime) override;
    void Input(glm::vec3& dir);

private:
    glm::vec3 velocity_;     // 현재 속도
    glm::vec3 direction_;    // 현재 입력 방향
    float acceleration_;     // 초당 가속도
    float maxSpeed_;         // 현재 적용되는 최대속도
};

