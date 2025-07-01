#include "TestActor.h"
#include "MeshComponent.h"
#include "GameGlobals.h"
#include "GameWorld.h"
#include "DirectionalLight.h"

TestActor::TestActor() : character_comp_(nullptr)
{
}

TestActor::~TestActor()
{
	Destory();
}

void TestActor::Start()
{
	character_comp_ = new MeshComponent(this, "Assets/NPC_Enzo_Model/obj/obj.obj");
	AddComponent(character_comp_);

	SetPosition(glm::vec3(3, -2.f, 0));
}

void TestActor::Update(float deltaTime)
{
	auto world = Game::World();
	Actor* dirLight = world->GetDirectionalLight();
	if (dirLight != nullptr)
	{
		float dAngle = (deltaTime / 1000.f) * angle_;
		
		cur_angle_ += dAngle;

		if (cur_angle_ > 360)
			cur_angle_ = cur_angle_ - 360;

		glm::vec3 pos = dirLight->GetPosition();

		pos.x = glm::sqrt(2) * glm::sin(cur_angle_);
		pos.z = glm::sqrt(2) * glm::cos(cur_angle_);

		glm::vec3 direction = glm::normalize(pos - glm::vec3(0));
		glm::vec3 sourceDir = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::quat rotationQuat = glm::rotation(sourceDir, direction);

		glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);
		glm::vec3 eulerAnglesDegree = glm::degrees(eulerAngles);

		dirLight->SetPosition(pos);
		dirLight->SetRotate(eulerAnglesDegree);
	}

	Actor::Update(deltaTime);
}

void FloorActor::Start()
{
	floor_comp_ = new MeshComponent(this, "Assets/base/Cube.obj");
	AddComponent(floor_comp_);

	SetPosition(glm::vec3(0.f, -2.f, 0.f));
	SetScale(glm::vec3(5.f, 0.1f, 5.f));
}
