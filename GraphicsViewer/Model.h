#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <memory>

class Mesh;
class Shader;
class Texture;

namespace NAssimpTexture
{
	static std::vector<aiTextureType>& GetAssimpTextureList();
}

// 일단 모델만 스마트 포인터 사용함.
class Model : public std::enable_shared_from_this<Model>
{
public:
	Model();
	~Model();

	void Load(const std::string& filePath);
	void Unload();
	void Draw(Shader& shader);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessMaterial(aiMaterial* material, std::vector<Texture>& textures);
	void AddTexture(std::string& path, int type);
	std::vector<Mesh> meshes_;
	std::map<std::string, Texture> texPaths_;
	std::string path_;
};

