#pragma once
#include "Actor.h"

struct DirectionalLight
{
	// 방향광
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// 기본 세기
	float ambientStrength;
	float specularPow;
	float specularStrength;
};

class DirectionalLightActor : public Actor
{
public:
	DirectionalLightActor();
	~DirectionalLightActor();

	void init();

	DirectionalLight& GetDirectionalLight() { return dl_; }

private:
	DirectionalLight dl_;
};
