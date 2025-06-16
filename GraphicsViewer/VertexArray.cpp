#include "VertexArray.h"

VertexArray::VertexArray(const std::vector<Vertex>& vertices, unsigned int vertexCount, const unsigned int* index, unsigned int indexCount) : vertex_count_(vertexCount), index_count_(indexCount)
{
	// 버텍스 배열 객체 생성
	glGenVertexArrays(1, &vertex_array_);
	// 현재 버텍스 활성화
	glBindVertexArray(vertex_array_);

	// 버텍스 버퍼 생성
	glGenBuffers(1, &vertex_buffer_);
	// 버텍스 버퍼 활성화
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	// 활성화된 버퍼에 vertex셋팅
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count_, &vertices[0], GL_STATIC_DRAW);

	// 인데스 버퍼 생성
	glGenBuffers(1, &index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count_, index, GL_STATIC_DRAW);

	// 위치
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	// 노멀
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	// 텍스처
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coord)));
}

VertexArray::~VertexArray()
{
}

void VertexArray::SetActive()
{
	glBindVertexArray(vertex_array_);
}

void VertexArray::Released()
{
	// 일단 생각해보기
	glDeleteBuffers(1, &vertex_buffer_);
	glDeleteBuffers(1, &index_buffer_);
	glDeleteVertexArrays(1, &vertex_array_);
}
