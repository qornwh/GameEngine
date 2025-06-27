#pragma once
#include<vector>
#include "Shader.h"
#include "Texture.h"
#include "ShadowFBO.h"

class MeshComponent;
class Texture;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void LoadShader();
	void Draw();
	void AddMeshComponent(MeshComponent* component);
	void RemoveMeshComponent(MeshComponent* component);

	Texture& GetDefaultTexture();
private:
	void SceneDraw(Shader& shader);

	std::vector<MeshComponent*> comps_;
	Shader shader_;
	Shader shadowShader_;
	ShadowFBO shadowFBO_;
	Texture texture_;
};

