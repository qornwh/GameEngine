#include "TestActor.h"
#include "MeshComponent.h"
#include "GameGlobals.h"
#include "GameWorld.h"
#include "DirectionalLight.h"

TestActor::TestActor() : mesh_comp_(nullptr)
{
}

TestActor::~TestActor()
{
	Destory();
}

void TestActor::Start()
{
	mesh_comp_ = new MeshComponent(this, "Assets/NPC_Enzo_Model/obj/obj.obj");
	AddComponent(mesh_comp_);
}

void TestActor::Update(float deltaTime)
{
	auto world = Game::World();
	Actor* dirLight = world->GetDirectionalLight();
	if (dirLight != nullptr)
	{
		auto& roate = dirLight->GetRotate();
		auto forward = dirLight->GetForward();
		float dAngle = (deltaTime / 1000.f) * angle_;
		
		roate.y += dAngle;
		if (roate.y >= 360)
			roate.y -= 360.f;
	}
}
