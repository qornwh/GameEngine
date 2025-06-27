#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class Renderer;
class Actor;
class Model;
class CameraActor;
class DirectionalLightActor;
class ActorFactory;

using ModelPtr = std::shared_ptr<Model>;

class GameWorld
{
	friend class GameEngine;
public:
	GameWorld();
	~GameWorld();

	virtual void Start() {};
	virtual void End() {};

	bool DespawnActor(Actor* actor);
	bool DespawnActor(Actor* parent, Actor* actor);

	ModelPtr GetModel(const std::string& fileName);
	Renderer* GetRenderer() { return renderer_; }
	void SetMainCamera(CameraActor* actor);
	CameraActor* MainCamera() { return main_camera_; }
	void SetDirectionalLight(DirectionalLightActor* actor);
	DirectionalLightActor* GetDirectionalLight() { return dl_; }

	Actor* GetRootActor() { return root_actor_; }
	ActorFactory* GetActorFactory() { return actor_factory_; }
	
protected:
	virtual void AfterUpdate() {};

private:
	void Update();
	Renderer* renderer_;
	CameraActor* main_camera_;
	DirectionalLightActor* dl_;
	float time_ = 0;

	// root
	Actor* root_actor_;
	ActorFactory* actor_factory_;

	// 중복 메시 로딩 최소화 (중간에 텍스처 갈아끼우는 경우는 없을 것이다. 그럴 경우 그냥 다른 model을 추가한다.)
	std::unordered_map<std::string, ModelPtr> models_;
};
