#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <GLFW/glfw3.h>

Mesh::Mesh(VertexArray vao, std::vector<Texture> textures) : vao_(vao)
{
    textures_ = textures;

    for (auto& texture : textures)
    {
        material_.SetTexture(texture);
    }
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader)
{
    for (int i = 0; i < textures_.size(); ++i)
    {
        auto& texture = textures_[i];
        texture.SetActive(shader);
    }
    vao_.SetActive();
    glDrawElements(GL_TRIANGLES, vao_.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::SetActive()
{
}

void Mesh::Unload()
{
    vao_.Released();
    for (auto& texture : textures_)
    {
        texture.Unload();
    }
    textures_.clear();
}
