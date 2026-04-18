#include "CameraActor.h"
#include "Macro.h"
#include "GameGlobals.h"
#include "GameWorld.h"
#include "GameEngine.h"
#include "MouseInput.h"
#include "KeyBoardInput.h"

CameraActor::CameraActor(float distance, CameraMode mode) : Actor(), distance_(distance), mode_(mode)
{
	const float w = static_cast<float>(DefaultWindowWidth);
	const float h = static_cast<float>(DefaultWindowHeight);
	perspective_ = glm::perspective(glm::radians(fov_), w / h, 0.1f, 100.f);
	orthographic_ = glm::ortho(0.f, w, 0.f, h, 0.1f, 100.f);
}

CameraActor::~CameraActor()
{
}

glm::mat4 CameraActor::GetProjection()
{
	auto& engine = GameEngine::GetInstance();
	const float w = static_cast<float>(engine.GetWidth());
	const float h = static_cast<float>(engine.GetHeight());
	const float aspect = engine.GetAspect();

	switch (mode_)
	{
	case CameraMode::Perspective3D:
		return glm::perspective(glm::radians(fov_), aspect, 0.1f, 100.f);

	case CameraMode::Ortho3D:
	{
		// 3D 직교: 월드 단위 기준, 종횡비 유지, 중앙 원점
		float halfH = distance_;
		float halfW = halfH * aspect;
		return glm::ortho(-halfW, halfW, -halfH, halfH, 0.1f, 100.f);
	}

	case CameraMode::Ortho2D:
	{
		// 2D: 화면 중앙 원점, zoom 반영
		float halfW = (w * 0.5f) / zoom_;
		float halfH = (h * 0.5f) / zoom_;
		return glm::ortho(-halfW, halfW, -halfH, halfH, -1.f, 1.f);
	}
	}
	return glm::mat4(1.f);
}

glm::mat4 CameraActor::GetView()
{
	if (mode_ == CameraMode::Ortho2D)
	{
		// 2D: 단순 역이동
		glm::vec2 p(GetPosition().x, GetPosition().y);
		return glm::translate(glm::mat4(1.f), glm::vec3(-p, 0.f));
	}

	glm::mat4 view = glm::lookAt(GetPosition(), GetPosition() + GetForward(), vec3Up);
	return view;
}

void CameraActor::SetActive()
{
	// 주 카메라가 됨
	Game::World()->SetMainCamera(this);
}

glm::vec3 CameraActor::GetForward()
{
	// 카메라만 전방벡터 따로 간다?
	float yawRad = glm::radians(GetRotate().x);
	float pitchRad = glm::radians(GetRotate().y);

	glm::vec3 forward;
	forward.x = cos(pitchRad) * sin(yawRad);
	forward.y = sin(pitchRad);
	forward.z = -cos(pitchRad) * cos(yawRad);
	return glm::normalize(forward);
}

void CameraActor::Update(float deltaTime)
{
	//float x = MouseInput::GetInstance().GetX();
	//float y = MouseInput::GetInstance().GetY();

	//if (!isFirst)
	//{
	//	last_pos_x_ = x;
	//	last_pos_y_ = y;
	//	isFirst = true;
	//	return;
	//}

	//float offsetX = (x - last_pos_x_) * sensitivity_;
	//float offsetY = (last_pos_y_ - y) * sensitivity_;

	//last_pos_x_ = x;
	//last_pos_y_ = y;

	//float yaw = GetRotate().x;
	//float pitch = GetRotate().y;
	//float roll = GetRotate().z;

	//yaw += offsetX;
	//pitch += offsetY;

	//if (pitch > 89.f)
	//	pitch = 89.f;
	//else if (pitch < -89.f)
	//	pitch = -89.f;

	//SetRotate(glm::vec3(yaw, pitch, roll));
}
