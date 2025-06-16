#include "TestGameWorld.h"
#include "TestActor.h"
#include "CameraActor.h"
#include "ImGuiActor.h"

#include "DirectionalLight.h"

void TestGameWorld::Start()
{
	TestActor* actor = new TestActor();
	actor->Start();

	CameraActor* camera = new CameraActor();
	camera->SetPosition(glm::vec3(0.f, 0.f, 10.f));

	SetMainCamera(camera);
	imgui_actor_ptr_ = std::make_shared<ImGuiActor>();
	imgui_actor_ptr_->SetActor(actor);

	DirectionalLightActor* directionalLight = new DirectionalLightActor();
	directionalLight->init();
	SetDirectionalLight(directionalLight);

	AddActor(actor);
}

void TestGameWorld::AfterUpdate()
{
	imgui_actor_ptr_->Draw();
}
