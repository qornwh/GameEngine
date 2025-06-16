#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include <iostream>

Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const std::string& fileName)
{
	Assimp::Importer import;
	auto flag = aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals;
	// ÁÂÇ¥ (0,0) ÁÂÇ¥°¡ ¿ÞÂÊ ¾Æ·¡ / (0,0)ÀÌ ¿ÞÂÊ À§ °¢ ´Ù¸§
	//auto flag = aiProcess_CalcTangentSpace |
	//	aiProcess_Triangulate |
	//	aiProcess_GenSmoothNormals |
	//	aiProcess_FlipUVs;
	const aiScene* scene = import.ReadFile(fileName, flag);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Not Load Model !!!" << '\n';
		return;
	}

	auto last = fileName.find_last_of('/') + 1;
	path_ = fileName.substr(0, last);

	ProcessNode(scene->mRootNode, scene);
}

void Model::Unload()
{
	for (auto& mesh : meshes_)
	{
		mesh.Unload();
	}
}

void Model::Draw(Shader& shader)
{
	for (auto& mesh : meshes_)
	{
		mesh.Draw(shader);
	}
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(ProcessMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertexs;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;

		auto& position = vertex.position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			auto& normal = vertex.normal;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
		}

		auto& uv = vertex.tex_coord;
		if (mesh->mTextureCoords[0])
		{
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			uv.x = 0.f;
			uv.y = 0.f;
		}

		vertexs.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		aiString texPath;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS) {
			
			std::string path(path_); 
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
			std::cout << "Diffuse texture file: " << texPath.C_Str() << " - " << iter->second.GetId() << std::endl;
		}
		/*if (material->GetTexture(aiTextureType_SPECULAR, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Specular texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_NORMALS, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Normals texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_HEIGHT, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Height texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_AMBIENT, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Ambient texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_EMISSIVE, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Emissive texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_OPACITY, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Opacity texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_METALNESS, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Metalness texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Diffus Roughness texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}
		if (material->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &texPath) == AI_SUCCESS) {
			std::cout << "Ambient Occlusion texture file: " << texPath.C_Str() << std::endl;

			std::string path(path_);
			path.append(texPath.data);
			AddTexture(path);
			auto iter = texPaths_.find(path);
			if (iter != texPaths_.end())
			{
				textures.push_back(iter->second);
			}
		}*/
	}

	VertexArray vao(vertexs, vertexs.size(), indices.data(), indices.size());
	return Mesh(vao, textures);
}

void Model::AddTexture(std::string& path)
{
	auto iter = texPaths_.find(path);
	if (iter == texPaths_.end())
	{
		aiString resultPath(path_);
		resultPath.Append(path.c_str());
		Texture texture;
		texture.Load(path.c_str());
		texPaths_.emplace(path, texture);
	}
}
