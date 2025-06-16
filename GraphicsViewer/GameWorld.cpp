#include "GameWorld.h"
#include "Actor.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "Model.h"
#include <GLFW/glfw3.h>

GameWorld::GameWorld()
{
	time_ = glfwGetTime();
	renderer_ = new Renderer();
	renderer_->LoadShader();
}

GameWorld::~GameWorld()
{
	if (renderer_ != nullptr)
		delete renderer_;
}

void GameWorld::Update()
{
	// 인풋입력
	// 현재 입력된 모든 입력 엑터에 넘기기 or 전역변수 등록후 액터,컴포넌트에서 가져와서 처리

	// 액터 업데이트
	float deltaTime = (glfwGetTime() - time_) * 1000.f;
	time_ = glfwGetTime();
	for (auto actor : actors_)
	{
		actor->Update(deltaTime);
	}

	// 그리기
	renderer_->Draw();
}

void GameWorld::AddActor(Actor* actor)
{
	auto iter = std::find(actors_.begin(), actors_.end(), actor);

	if (iter == actors_.end())
	{
		actors_.push_back(actor);
	}
}

bool GameWorld::DestoryActor(Actor* actor)
{
	auto iter = std::find(actors_.begin(), actors_.end(), actor);

	if (iter != actors_.end())
	{
		actors_.erase(iter);
		return true;
	}
	return false;
}

ModelPtr GameWorld::GetModel(const std::string& fileName)
{
	auto it = models_.find(fileName);
	if (it == models_.end())
	{
		ModelPtr ptr = std::make_shared<Model>();
		ptr->Load(fileName);
		models_.emplace(fileName, ptr);
	}
	return models_[fileName];
}

void GameWorld::SetMainCamera(CameraActor* actor)
{
	main_camera_ = actor;
}

void GameWorld::SetDirectionalLight(DirectionalLightActor* actor)
{
	dl_ = actor;
}
