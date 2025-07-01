#include "TestGameWorld.h"
#include "TestActor.h"
#include "CameraActor.h"
#include "ImGuiActor.h"
#include "ActorFactory.h"
#include "GameEngine.h"
#include "GameGlobals.h"

#include "DirectionalLight.h"
#include "CubeActor.h"
#include <GLFW/glfw3.h>

void TestGameWorld::Start()
{
	TestActor* actor = Game::AFactory()->SpawnActor<TestActor>();
	actor->Start();

	CubeActor* cube1 = Game::AFactory()->SpawnActor<CubeActor>();
	cube1->SetScale(glm::vec3(0.2, 0.2, 0.2));
	cube1->SetPosition(glm::vec3(-1.5, 0, 1.5));

	CubeActor* cube2 = Game::AFactory()->SpawnActor<CubeActor>();
	cube2->SetScale(glm::vec3(0.2, 0.2, 0.2));
	cube2->SetPosition(glm::vec3(1.5, -1.5, -1.5));

	CubeActor* cube3 = Game::AFactory()->SpawnActor<CubeActor>();
	cube3->SetScale(glm::vec3(0.2, 0.2, 0.2));
	cube3->SetPosition(glm::vec3(-1.5, -1.5, -1.5));

	FloorActor* actor2 = Game::AFactory()->SpawnActor<FloorActor>();
	actor2->Start();

	CameraActor* camera = Game::AFactory()->SpawnActor<CameraActor>();
	camera->SetPosition(glm::vec3(0.f, 0.f, 10.f));

	DirectionalLightActor* directionalLight = new DirectionalLightActor();
	directionalLight->init();

	directionalLight->SetPosition(glm::vec3(1.f, 1.f, 1.f));
	SetDirectionalLight(directionalLight);

	SetMainCamera(camera);

	imgui_actor_ptr_ = std::make_shared<ImGuiActor>();
	imgui_actor_ptr_->SetActor(camera);
	imgui_actor_ptr_->SetActor2(actor);
}

void TestGameWorld::AfterUpdate()
{
	imgui_actor_ptr_->Draw();
}
