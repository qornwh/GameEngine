#include "Actor.h"
#include <algorithm>

Actor::Actor()
{
	scale_ = glm::vec3(1.f, 1.f, 1.f);
	position_ = glm::vec3(0.f, 0.f, 0.f);
	rotate_ = glm::vec3(0.f, 0.f, 0.f);
}

Actor::~Actor()
{
}

void Actor::Init(glm::vec3 position, glm::vec3 rotate)
{
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
}

void Actor::AddChild(Actor* child)
{
	children_.emplace_back(child);
}

void Actor::RemoveChild(Actor* child)
{
	auto iter = std::find(children_.begin(), children_.end(), child);

	if (iter != children_.end())
	{
		std::swap(*iter, children_.back());
		children_.pop_back();
	}
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

glm::vec3 Actor::GetForward()
{
	return glm::quat(rotate_) * vec3Forword;
}
