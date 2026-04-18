#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	// 버텍스 / 프래그먼트 쉐이더 로드 
	bool Load(const char* vertexName, const char* fragmentName);
	// 쉐이더 언로드
	void unLoad();
	// 쉐이더 활성화
	void SetActive();

	void SetUniformInt(const char* name, int value);
	void SetUniformFloat(const char* name, float value);
	void SetUniformVec2(const char* name, const glm::vec2& value);
	void SetUniformVec3(const char* name, const glm::vec3& value);
	void SetUniformMat3(const char* name, const glm::mat3& value);
	void SetUniformMat4(const char* name, const glm::mat4& value);

private:
	// 쉐이더 컴파일
	bool CompileShader(const char* fileName, GLenum shaderType, GLenum& shader);
	// 쉐이더 컴파일 성공여부
	bool IsCompiled(GLenum shader);
	// 쉐이더 프로그램 링크 성공여부
	bool IsLinked();

	GLenum vertex_shader_;
	GLenum fragment_shader_;
	GLenum shader_program_;
};

