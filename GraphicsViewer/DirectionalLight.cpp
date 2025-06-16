#include "DirectionalLight.h"

DirectionalLightActor::DirectionalLightActor() : Actor()
{
}

DirectionalLightActor::~DirectionalLightActor()
{
}

void DirectionalLightActor::init()
{
	SetRotate(vec3Up);

	dl_.ambientStrength = 1.f;
	dl_.ambient = glm::vec3(0.2f, 0.2f, 0.2f);

	dl_.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);

	dl_.specularPow = 32;
	dl_.specularStrength = 0.5f;
	dl_.specular = glm::vec3(0.8f, 0.8f, 0.8f);
}
