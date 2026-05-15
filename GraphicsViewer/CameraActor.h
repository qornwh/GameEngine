#pragma once
#include "Actor.h"

enum class CameraMode
{
	Perspective3D,
	Ortho3D,
	Ortho2D,
};

class CameraActor : public Actor
{
public:
	CameraActor(float distance = 1.f, CameraMode mode = CameraMode::Perspective3D);
	~CameraActor();

	glm::mat4& GetPerspective() { return perspective_; }
	glm::mat4& GetOrthographic() { return orthographic_; }
	glm::mat4 GetProjection();

	void SetDistacne(float distance) { distance_ = distance; }
	float GetDistance() { return distance_; }

	void SetMode(CameraMode mode) { mode_ = mode; }
	CameraMode GetMode() const { return mode_; }

	void SetPerspective(bool value) { mode_ = value ? CameraMode::Perspective3D : CameraMode::Ortho3D; }
	bool IsProjection() { return mode_ == CameraMode::Perspective3D; }

	void SetZoom(float z) { zoom_ = z; }
	float GetZoom() const { return zoom_; }

	void SetActive();

	glm::mat4 GetView();

	void Update(float deltaTime) override;

private:
	// 카메라
	float fov_ = 20.0f;
	glm::mat4 perspective_;
	glm::mat4 orthographic_;

	// 포지션에서 타겟까지 거리 => 카메라 암
	float distance_;
	CameraMode mode_;

	bool isFirst = false;
	float last_pos_x_ = 0;
	float last_pos_y_ = 0;
	float sensitivity_ = 0.05f;

	// 2D 모드 줌 배율
	float zoom_ = 1.f;
};
