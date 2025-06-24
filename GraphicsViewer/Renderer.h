#pragma once
#include<vector>
#include "Shader.h"
#include "Texture.h"

class MeshComponent;
class Texture;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void LoadShader();
	void Draw();
	void AddMeshComponent(MeshComponent* component);
	void RemoveMeshComponent(MeshComponent* component);

	Texture& GetDefaultTexture();
private:
	std::vector<MeshComponent*> comps_;
	Shader shader_;
	Texture texture_;
};

