#include "PlayerActor.h"
#include "MovementComponent.h"
#include "CameraActor.h"
#include "KeyBoardInput.h"
#include "MouseInput.h"

PlayerActor::PlayerActor()
{
}

PlayerActor::~PlayerActor()
{
}

void PlayerActor::Start()
{
	moveComp_ = new MovementComponent(this);
}

void PlayerActor::Update(float deltaTime)
{
	CameraMove();

	if (moveComp_ != nullptr)
	{
		//glm::vec3 forward = GetForward();
		glm::vec3 inputDir(0.0f);

		// 기준은 카메라 방향
		glm::vec3 camForward = glm::normalize(glm::vec3(camera_->GetForward().x, camera_->GetForward().y, camera_->GetForward().z));
		glm::vec3 camRight = -glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), camForward)); // 오른쪽 벡터

		// 키보드 입력 → 입력 벡터 누적
		if (KeyBoardInput::GetInstance().GetKey(GLFW_KEY_W))
			inputDir += camForward;
		if (KeyBoardInput::GetInstance().GetKey(GLFW_KEY_S))
			inputDir -= camForward;
		if (KeyBoardInput::GetInstance().GetKey(GLFW_KEY_D))
			inputDir += camRight;
		if (KeyBoardInput::GetInstance().GetKey(GLFW_KEY_A))
			inputDir -= camRight;

		moveComp_->Input(inputDir);
		moveComp_->Update(deltaTime);
	}

	if (camera_ != nullptr)
	{
		camera_->SetRotate(GetRotate());
		camera_->SetPosition(GetPosition());
	}
}

void PlayerActor::SetCamera(CameraActor* camera)
{
	if (camera != nullptr)
	{
		camera_ = camera;
	}
}

void PlayerActor::CameraMove()
{
	float x = MouseInput::GetInstance().GetX();
	float y = MouseInput::GetInstance().GetY();

	if (!isFirst)
	{
		last_pos_x_ = x;
		last_pos_y_ = y;
		isFirst = true;
		return;
	}

	float offsetX = (x - last_pos_x_) * sensitivity_;
	float offsetY = (last_pos_y_ - y) * sensitivity_;

	last_pos_x_ = x;
	last_pos_y_ = y;

	float yaw = GetRotate().x;
	float pitch = GetRotate().y;
	float roll = GetRotate().z;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.f)
		pitch = 89.f;
	else if (pitch < -89.f)
		pitch = -89.f;

	SetRotate(glm::vec3(yaw, pitch, roll));
}
