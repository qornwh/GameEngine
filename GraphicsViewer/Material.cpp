#include "Material.h"
#include <GL/glew.h>
#include <assimp/material.h>
#include "Shader.h"

void Material::SetActive(Shader& shader)
{
	if (IsDeffuse)
	{
		glActiveTexture(GL_TEXTURE0);
		deffuse_.SetActive(shader);
		//shader.SetUniformInt("uMaterial.deffuse", 0);
	}
	else if (IsMetallic)
	{
		glActiveTexture(GL_TEXTURE1);
		metallic_.SetActive(shader);
	}
	else if (IsRoughness)
	{
		glActiveTexture(GL_TEXTURE2);
		roughness_.SetActive(shader);
	}
	else if (IsNormal)
	{
		glActiveTexture(GL_TEXTURE3);
		normal_.SetActive(shader);
	}
	else if (IsAO)
	{
		glActiveTexture(GL_TEXTURE4);
		ao_.SetActive(shader);
	}
	else if (IsEmissive)
	{
		glActiveTexture(GL_TEXTURE5);
		emissive_.SetActive(shader);
	}
}

void Material::SetTexture(Texture& texture)
{
	int texType = texture.GetType();
	if (texType == aiTextureType_DIFFUSE || texType == aiTextureType_BASE_COLOR)
	{
		IsDeffuse = true;
		deffuse_ = texture;
	}
	else if (texType == aiTextureType_METALNESS)
	{
		IsMetallic = true;
		metallic_ = texture;
	}
	else if (texType == aiTextureType_DIFFUSE_ROUGHNESS)
	{
		IsRoughness = true;
		roughness_ = texture;
	}
	else if (texType == aiTextureType_NORMALS)
	{
		IsNormal = true;
		normal_ = texture;
	}
	else if (texType == aiTextureType_AMBIENT_OCCLUSION)
	{
		IsAO = true;
		ao_ = texture;
	}
	else if (texType == aiTextureType_EMISSIVE)
	{
		IsEmissive = true;
		emissive_ = texture;
	}
}
