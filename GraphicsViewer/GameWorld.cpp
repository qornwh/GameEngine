#include "GameWorld.h"
#include "Actor.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "Model.h"
#include "ActorFactory.h"
#include <GLFW/glfw3.h>

GameWorld::GameWorld()
{
	time_ = static_cast<float>(glfwGetTime());
	renderer_ = new Renderer();
	renderer_->LoadShader();
	root_actor_ = new Actor();
	actor_factory_ = new ActorFactory();
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
	float deltaTime = (static_cast<float>(glfwGetTime()) - time_) * 1000.f;
	time_ = static_cast<float>(glfwGetTime());
	root_actor_->Update(deltaTime);

	// 그리기
	renderer_->Draw();
}

bool GameWorld::DespawnActor(Actor* actor)
{
	return DespawnActor(root_actor_, actor);
}

bool GameWorld::DespawnActor(Actor* parent, Actor* actor)
{
	if (parent != nullptr)
	{
		auto iter = std::find(parent->GetChildren().begin(), parent->GetChildren().end(), actor);
		if (iter != parent->GetChildren().end())
		{
			return parent->RemoveChild(reinterpret_cast<Actor*>(actor));
		}
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
