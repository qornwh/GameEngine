#pragma once
#include "Actor.h"

class CameraActor : public Actor
{
public:
	CameraActor(float distance = 1.f, bool is_perspective = true);
	~CameraActor();

	glm::mat4& GetPerspective() { return perspective_; }
	glm::mat4& GetOrthographic() { return orthographic_; }
	glm::mat4 GetProjection();

	void SetDistacne(float distance) { distance_ = distance; }
	float GetDistance() { return distance_; }

	void SetPerspective(bool value) { is_perspective_ = value; };
	bool IsProjection() { return is_perspective_; }

	glm::mat4 GetView();

	void SetActive();

	glm::vec3 GetForward() override;

private:
	// 카메라 
	float fov_ = 20.0f;
	glm::mat4 perspective_;
	glm::mat4 orthographic_;
	
	// 포지션에서 타겟까지 거리 => 카메라 암
	float distance_;
	bool is_perspective_;
};

