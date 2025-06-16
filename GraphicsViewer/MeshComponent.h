#pragma once
#include "Component.h"
#include <memory>
#include <string>

class Model;
class Actor;

using ModelPtr = std::shared_ptr<Model>;

class MeshComponent : public Component
{
public:
	MeshComponent(Actor* actor, const std::string& modelName);
	~MeshComponent();

	void Remove() override;
	ModelPtr GetModelPtr() { return model_ptr_; }
private:
	ModelPtr model_ptr_;
};
