#include "CameraActor.h"
#include "Macro.h"
#include "GameGlobals.h"
#include "GameWorld.h"

CameraActor::CameraActor(float distance, bool is_perspective) : Actor(), distance_(distance), is_perspective_(is_perspective)
{
	perspective_ = glm::perspective(glm::radians(fov_), 1024.f / 720.f, 0.1f, 100.f);
	orthographic_ = glm::ortho(0.f, 1024.f, 0.f, 720.f, 0.1f, 100.f);
}

CameraActor::~CameraActor()
{
}

glm::mat4 CameraActor::GetProjection()
{
	if (is_perspective_)
		return glm::perspective(glm::radians(fov_), 1024.f / 720.f, 0.1f, 100.f);
	else
		return glm::ortho(0.f, 1024.f, 0.f, 720.f, 0.1f, 100.f);
}

glm::mat4 CameraActor::GetView()
{
	glm::mat4 view = glm::lookAt(GetPosition(), GetPosition() + GetForward(), vec3Up);
	return view;
}

void CameraActor::SetActive()
{
	// 주 카메라가 됨
	Game::World()->SetMainCamera(this);
}
