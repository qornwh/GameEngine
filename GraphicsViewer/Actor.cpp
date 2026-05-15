#include "Actor.h"
#include <algorithm>
#include "Component.h"
#include "GameWorld.h"
#include "GameGlobals.h"

Actor::Actor()
{
	scale_ = glm::vec3(1.f, 1.f, 1.f);
	position_ = glm::vec3(0.f, 0.f, 0.f);
	rotate_ = glm::vec3(0.f, 0.f, 0.f);
	quaternion_ = glm::quat(1.f, 0.f, 0.f, 0.f);
}

Actor::~Actor()
{
}

void Actor::Update(float deltaTime)
{
	for (auto child : GetChildren())
	{
		child->Update(deltaTime);
	}
}

void Actor::Destory()
{
	for (auto child : GetChildren())
	{
		child->Destory();
		delete child;
	}

	for (auto comp : GetComponent())
	{
		comp->Remove();
		delete comp;
	}

	GameWorld* world = Game::World();
	if (world)
	{
		world->DespawnActor(this);
	}
}

void Actor::Init(glm::vec3 position, glm::vec3 rotate)
{
	SetPosition(position);
	SetRotate(rotate);
}

void Actor::SetScale(const glm::vec3& scale)
{
	scale_ = scale;
}

void Actor::SetPosition(const glm::vec3& position)
{
	position_ = position;
}

void Actor::SetRotate(const glm::vec3& rotate)
{
	rotate_ = rotate;
	quaternion_ = glm::quat(glm::radians(rotate_));
}

void Actor::SetQuaternion(const glm::quat& quaternion)
{
	quaternion_ = glm::normalize(quaternion);
	rotate_ = glm::degrees(glm::eulerAngles(quaternion_));
}

void Actor::LookAt(const glm::vec3& target, const glm::vec3& up)
{
	glm::vec3 direction = target - position_;
	if (glm::dot(direction, direction) <= 0.000001f)
	{
		return;
	}

	glm::vec3 forward = glm::normalize(direction);
	glm::vec3 right = glm::cross(forward, up);

	if (glm::dot(right, right) <= 0.000001f)
	{
		glm::vec3 fallbackUp = glm::abs(glm::dot(forward, vec3UnitZ)) > 0.999f ? vec3UnitY : vec3UnitZ;
		right = glm::cross(forward, fallbackUp);
	}

	right = glm::normalize(right);
	glm::vec3 correctedUp = glm::normalize(glm::cross(right, forward));

	glm::mat3 rotation;
	rotation[0] = right;
	rotation[1] = correctedUp;
	rotation[2] = -forward;
	SetQuaternion(glm::quat_cast(rotation));
}

void Actor::AddChild(Actor* child)
{
	children_.emplace_back(child);
}

bool Actor::RemoveChild(Actor* child)
{
	auto iter = std::find(children_.begin(), children_.end(), child);

	if (iter != children_.end())
	{
		std::swap(*iter, children_.back());
		children_.pop_back();
		delete child;
		return true;
	}
	return false;
}

void Actor::AddComponent(Component* comp)
{
	components_.push_back(comp);
}

void Actor::RemoveComponent(Component* comp)
{
	auto iter = std::find(components_.begin(), components_.end(), comp);

	if (iter != components_.end())
	{
		std::swap(*iter, components_.back());
		components_.pop_back();
	}
}

glm::vec3 Actor::GetForwardVector()
{
	return glm::normalize(quaternion_ * vec3Forword);
}

glm::vec3 Actor::GetRightVector()
{
	return glm::normalize(quaternion_ * vec3Right);
}

glm::vec3 Actor::GetUpVector()
{
	return glm::normalize(quaternion_ * vec3Up);
}
