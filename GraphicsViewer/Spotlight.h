#pragma once
#include "Actor.h"

struct Spotlight
{
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// 코싸인값 -> 성능상 내젹결과만 비교
	float cutOff;
};

class SpotlightActor
{
public:
	SpotlightActor();
	~SpotlightActor();

	void init();
	void SetRadius(float radius);

	Spotlight& GetSpotlight() { return sl_; }
private:
	Spotlight sl_;
	float radius_;
};

