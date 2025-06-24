#include "Spotlight.h"

SpotlightActor::SpotlightActor()
{
}

SpotlightActor::~SpotlightActor()
{
}

void SpotlightActor::init()
{
	sl_.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	sl_.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	sl_.specular = glm::vec3(0.8f, 0.8f, 0.8f);

	SetRadius(30.f);
}

void SpotlightActor::SetRadius(float radius)
{
	radius_ = radius;
	sl_.cutOff = glm::cos(glm::radians(radius));
}
