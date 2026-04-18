#pragma once
#include <vector>
#include "VertexArray.h"
#include "Material.h"

class Shader;
class Texture;

class Mesh
{
public:
	Mesh(VertexArray vao, std::vector<Texture> textures);
	~Mesh();

	void Draw(Shader& shader);
	void SetActive();
	void Unload();

private:
	VertexArray vao_;
	std::vector<Texture> textures_;
	Material material_;
};

