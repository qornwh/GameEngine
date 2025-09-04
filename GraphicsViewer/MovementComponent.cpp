#include "MovementComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* actor) 
    : Component(actor),
    velocity_(0.0f),
    direction_(0.0f),
    acceleration_(5.0f),
    maxSpeed_(2.5f)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(float deltaTime)
{
    if (glm::length2(direction_) > 0.0001f)
    {
        glm::vec3 moveDir = glm::normalize(direction_);
        velocity_ += moveDir * acceleration_ * (deltaTime / 1000);

        if (glm::length2(velocity_) > maxSpeed_ * maxSpeed_)
            velocity_ = glm::normalize(velocity_) * maxSpeed_;
    }
    else
    {
        velocity_ = glm::mix(velocity_, glm::vec3(0.0f), (deltaTime / 1000) * 10.0f);
        if (glm::length2(velocity_) < 0.001f)
            velocity_ = glm::vec3(0.0f);
    }

    glm::vec3 pos = GetActor()->GetPosition();
    pos += velocity_ * (deltaTime / 1000);
    GetActor()->SetPosition(pos);

    // 입력 초기화 (프레임마다)
    direction_ = glm::vec3(0.0f);
}

void MovementComponent::Input(glm::vec3& dir)
{
	direction_ = dir;
}
