#pragma once
#include <vector>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include "ShadowFBO.h"

#define ASSERT(x)  if(!(x)) __debugbreak();
#define GLCheck(x) GLClearError();\
                   x;\
                   ASSERT(GLCheckError(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::string errStr = "";
		switch (error)
		{
		case GL_NO_ERROR:          errStr = "No Errors"; break;
		case GL_INVALID_ENUM:      errStr = "Invalid Enum"; break;
		case GL_INVALID_VALUE:     errStr = "Invalid Value"; break;
		case GL_INVALID_OPERATION: errStr = "Invalid Operation"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: errStr = "Invalid Framebuffer Operation"; break;
		case GL_OUT_OF_MEMORY:   errStr = "Out of Memory"; break;
		case GL_STACK_UNDERFLOW: errStr = "Stack Underflow"; break;
		case GL_STACK_OVERFLOW:  errStr = "Stack Overflow"; break;

		default: errStr = "Unknown"; break;
		}

		std::cout << "[OpenGL Error] - " << errStr << std::endl
			<< "Code : " << function << std::endl
			<< "Line : " << file << " : " << line << std::endl << std::endl;
		return false;
	}
	return true;
}

class MeshComponent;
class Texture;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void LoadShader();
	void Draw();
	void AddMeshComponent(MeshComponent* component);
	void RemoveMeshComponent(MeshComponent* component);

	Texture& GetDefaultTexture();
private:
	void SceneDraw(Shader& shader);

	std::vector<MeshComponent*> comps_;
	Shader shader_;
	Shader shadowShader_;
	ShadowFBO shadowFBO_;
	Texture texture_;
};

