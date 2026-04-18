#pragma once
#include "Actor.h"
#include <vector>

static std::vector<std::vector<float>> AttenuationList = {
	{7,    1.0f, 0.7f,    1.8f},
	{13,   1.0f, 0.35f,   0.44f},
	{20,   1.0f, 0.22f,   0.20f},
	{32,   1.0f, 0.14f,   0.07f},
	{50,   1.0f, 0.09f,   0.032f},
	{65,   1.0f, 0.07f,   0.017f},
	{100,  1.0f, 0.045f,  0.0075f},
	{160,  1.0f, 0.027f,  0.0028f},
	{200,  1.0f, 0.022f,  0.0019f},
	{325,  1.0f, 0.014f,  0.0007f},
	{600,  1.0f, 0.007f,  0.0002f},
	{3250, 1.0f, 0.0014f, 0.000007f}
};

struct PointLight
{
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// 상수항, 선형, 이차
	float constant;
	float linear;
	float quadratic;

	// 기본 세기
	float ambientStrength;
	float specularPow;
	float specularStrength;
};

class PointLightActor : public Actor
{
public:
	PointLightActor();
	~PointLightActor();

	void init();
	void SetDistance(int distance);

	PointLight& GetPointLight() { return pl_; }
private:
	PointLight pl_;
	int distance_;
};

