#pragma once
#include<vector>
#include "Shader.h"

class MeshComponent;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void LoadShader();
	void Draw();
	void AddMeshComponent(MeshComponent* component);
	void RemoveMeshComponent(MeshComponent* component);
private:
	std::vector<MeshComponent*> comps_;
	Shader shader_;
};

