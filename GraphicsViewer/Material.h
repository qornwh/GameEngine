#pragma once

#include "Texture.h"

class Shader;

class Material
{
	bool IsDeffuse = false;
	bool IsMetallic = false;
	bool IsRoughness = false;
	bool IsNormal = false;
	bool IsAO = false;
	bool IsEmissive = false;

	Texture deffuse_;
	Texture metallic_;
	Texture roughness_;
	Texture normal_;
	Texture ao_;
	Texture emissive_;

public:
	void SetActive(Shader& shader);
	void SetTexture(Texture& texture);
};

