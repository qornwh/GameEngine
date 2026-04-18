#include "MeshComponent.h"
#include "Component.h"
#include "GameGlobals.h"
#include "GameWorld.h"
#include "Renderer.h"
#include <iostream>

MeshComponent::MeshComponent(Actor* actor, const std::string& modelName) : Component(actor)
{
	auto world = Game::World();
	model_ptr_ = world->GetModel(modelName);

	if (model_ptr_.get() == nullptr)
	{
		std::cout << "Error Model Not Found !!!" << '\n';
	}

	world->GetRenderer()->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Remove()
{
	auto world = Game::World();
	world->GetRenderer()->RemoveMeshComponent(this);
}
