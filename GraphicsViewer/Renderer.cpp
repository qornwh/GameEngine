#include "Renderer.h"
#include <glm/glm.hpp>                   // 기본 타입, 연산
#include <glm/gtc/matrix_transform.hpp>  // 변환 함수
#include <glm/gtc/type_ptr.hpp>          // value_ptr (OpenGL 넘길 때)
#include <glm/gtc/quaternion.hpp>        // 쿼터니언
#include <glm/gtx/quaternion.hpp>        // 쿼터니언 변환 함수 (optional)
#include "GameWorld.h"
#include "Actor.h"
#include "CameraActor.h"
#include "DirectionalLight.h"
#include "MeshComponent.h"
#include "GameGlobals.h"
#include "Model.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::LoadShader()
{
	shader_.Load("Shaders/base.vert", "Shaders/phong.frag");
}

void Renderer::Draw()
{
	auto world = Game::World();
	auto camera = world->MainCamera();
	auto dirLight = world->GetDirectionalLight();

	if (camera == nullptr)
		return;

	if (dirLight == nullptr)
		return;

	auto projection = camera->GetProjection();
	auto view = camera->GetView();
	for (auto comp : comps_)
	{
		// 스케일 회전 위치
		glm::vec3& position = comp->GetActor()->GetPosition();
		glm::vec3& rotate = comp->GetActor()->GetRotate();
		glm::vec3& scale = comp->GetActor()->GetScale();
		glm::mat4 worldTransform = glm::mat4(1.0f);
		worldTransform = glm::translate(worldTransform, position);
		worldTransform = worldTransform * glm::toMat4(glm::quat(glm::radians(rotate)));
		worldTransform = glm::scale(worldTransform, scale);

		shader_.SetActive();
		shader_.SetUniformMat4("uView", view);
		shader_.SetUniformMat4("uProjection", projection);
		shader_.SetUniformMat4("uWorldTransform", worldTransform);

		// 방향광
		shader_.SetUniformVec3("uDirectLight.direction", dirLight->GetForward());
		auto& dl = dirLight->GetDirectionalLight();
		shader_.SetUniformVec3("uDirectLight.ambient", dl.ambient);
		shader_.SetUniformVec3("uDirectLight.diffuse", dl.diffuse);
		shader_.SetUniformVec3("uDirectLight.specular", dl.specular);

		shader_.SetUniformFloat("uDirectLight.ambientStrength", dl.ambientStrength);
		shader_.SetUniformFloat("uDirectLight.specularPow", dl.specularPow);
		shader_.SetUniformFloat("uDirectLight.specularStrength", dl.specularStrength);
		shader_.SetUniformVec3("uCameraPosition", camera->GetPosition());

		comp->GetModelPtr()->Draw(shader_);
	}
}

void Renderer::AddMeshComponent(MeshComponent* component)
{
	comps_.push_back(component);
}

void Renderer::RemoveMeshComponent(MeshComponent* component)
{
	auto it = std::find(comps_.begin(), comps_.end(), component);
	if (it != comps_.end())
	{
		comps_.erase(it);
	}
}
