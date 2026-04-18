#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coord;
};

class VertexArray
{
public:
	VertexArray(const std::vector<Vertex>& vertices, unsigned int vertexCount, const unsigned int* index, unsigned int indexCount);
	~VertexArray();

	void SetActive();
	void Released();

	GLenum GetVertexCount() { return vertex_count_; }
	GLenum GetIndexCount() { return index_count_; }
private:
	unsigned int vertex_count_;
	unsigned int index_count_;
	GLenum vertex_buffer_;
	GLenum index_buffer_;
	GLenum vertex_array_;
};

