#pragma once
#include "Macro.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class Component;

class Actor
{
public:
	Actor();
	~Actor();

	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	void Destory();

	void Init(glm::vec3 position = vec3Zero, glm::vec3 rotate = vec3Zero);
	void SetScale(const glm::vec3& scale);
	void SetPosition(const glm::vec3& position);
	void SetRotate(const glm::vec3& rotate);

	void AddChild(Actor* child);
	bool RemoveChild(Actor* child);
	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	glm::vec3& GetScale() { return scale_; }
	glm::vec3& GetPosition() { return position_; }
	glm::vec3& GetRotate() { return rotate_; }
	glm::vec3 GetForward();

	const std::vector<Actor*>& GetChildren() { return children_; }
	const std::vector<Component*>& GetComponent() { return components_; }

private:
	glm::vec3 scale_;
	glm::vec3 position_;
	glm::vec3 rotate_;

	std::vector<Actor*> children_;
	std::vector<Component*> components_;

	unsigned int actor_id_;
};

