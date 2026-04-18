#include "Renderer.h"

#include <GLFW/glfw3.h>
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
#include "GameEngine.h"

Renderer::Renderer()
{
	// 디폴트 텍스처 로드
	texture_.Load("Assets/base/base.png");
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
}

void Renderer::LoadShader()
{
	shadowFBO_.Init();
	shadowShader_.Load("Shaders/shadow.vert", "Shaders/shadow.frag");
	shader_.Load("Shaders/base.vert", "Shaders/phong.frag");
	shader_.SetActive();
	shader_.SetUniformInt("uDiffuse", 1);
	shader_.SetUniformInt("uShadow", 0);
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

	// 그림자 텍스처 깊이
	// 빛 공간 변환
	float nearPlane = 0.1f, farPlane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(dirLight->GetPosition(), glm::vec3(0.f), vec3Up);
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	shadowShader_.SetActive();
	shadowShader_.SetUniformMat4("uLightSpaceMatrix", lightSpaceMatrix);
	shadowFBO_.SetActive();

	glActiveTexture(GL_TEXTURE1);
	SceneDraw(shadowShader_);

	// 화면
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	auto& engine = GameEngine::GetInstance();
	glViewport(0, 0, engine.GetWidth(), engine.GetHeight());
	// 방향광
	shader_.SetActive();
	shader_.SetUniformVec3("uDirectLight.direction", dirLight->GetForward());
	auto& dl = dirLight->GetDirectionalLight();
	shader_.SetUniformVec3("uDirectLight.ambient", dl.ambient);
	shader_.SetUniformVec3("uDirectLight.diffuse", dl.diffuse);
	shader_.SetUniformFloat("uDirectLight.ambientStrength", dl.ambientStrength);
	shader_.SetUniformFloat("uDirectLight.specularPow", dl.specularPow);
	shader_.SetUniformFloat("uDirectLight.specularStrength", dl.specularStrength);
	shader_.SetUniformVec3("uCameraPosition", camera->GetPosition());

	shader_.SetUniformMat4("uLightSpaceMatrix", lightSpaceMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowFBO_.GetTexture());
	glActiveTexture(GL_TEXTURE1);

	auto projection = camera->GetProjection();
	auto view = camera->GetView();
	shader_.SetUniformMat4("uView", view);
	shader_.SetUniformMat4("uProjection", projection);
	SceneDraw(shader_);
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

Texture& Renderer::GetDefaultTexture()
{
	return texture_;
}

void Renderer::SceneDraw(Shader& shader)
{
	auto world = Game::World();
	auto camera = world->MainCamera();

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
		shader.SetUniformMat4("uWorldTransform", worldTransform);
		texture_.SetActive(shader);
		comp->GetModelPtr()->Draw(shader);
	}
}
