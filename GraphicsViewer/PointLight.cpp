#include "PointLight.h"
#include "MeshComponent.h"

PointLightActor::PointLightActor() : Actor()
{
	MeshComponent* comp = new MeshComponent(this, "Assets/base/Cube.obj");

	AddComponent(comp);
}

PointLightActor::~PointLightActor()
{
	Destory();
}

void PointLightActor::init()
{
	pl_.ambientStrength = 1.f;
	pl_.ambient = glm::vec3(0.2f, 0.2f, 0.2f);

	pl_.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);

	pl_.specularPow = 32;
	pl_.specularStrength = 0.5f;
	pl_.specular = glm::vec3(0.8f, 0.8f, 0.8f);

	SetDistance(7);
}

void PointLightActor::SetDistance(int distance)
{
	distance_ = distance;

	int i = 0;
	for (i = 0; i < AttenuationList.size(); ++i)
	{
		auto& attenuation = AttenuationList[i];
		if (distance <= attenuation[0])
			break;
	}

	pl_.constant = AttenuationList[i][1];
	pl_.linear = AttenuationList[i][2];
	pl_.quadratic = AttenuationList[i][3];
}
