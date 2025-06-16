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

using ModelPtr = std::shared_ptr<Model>;

class GameWorld
{
	friend class GameEngine;
public:
	GameWorld();
	~GameWorld();

	virtual void Start() {};
	virtual void End() {};

	void AddActor(Actor* actor);
	bool DestoryActor(Actor* actor);

	ModelPtr GetModel(const std::string& fileName);
	Renderer* GetRenderer() { return renderer_; }
	void SetMainCamera(CameraActor* actor);
	CameraActor* MainCamera() { return main_camera_; }
	void SetDirectionalLight(DirectionalLightActor* actor);
	DirectionalLightActor* GetDirectionalLight() { return dl_; }
	
protected:
	virtual void AfterUpdate() {};

private:
	void Update();
	Renderer* renderer_;
	CameraActor* main_camera_;
	DirectionalLightActor* dl_;
	std::vector<Actor*> actors_;
	float time_ = 0;

	// 중복 메시 로딩 최소화
	std::unordered_map<std::string, ModelPtr> models_;
};
