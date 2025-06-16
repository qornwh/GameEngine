#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const char* vertexName, const char* fragmentName)
{
    if (!CompileShader(vertexName, GL_VERTEX_SHADER, vertex_shader_) || !CompileShader(fragmentName, GL_FRAGMENT_SHADER, fragment_shader_))
    {
        return false;
    }

    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader_);
    glAttachShader(shader_program_, fragment_shader_);
    glLinkProgram(shader_program_);

    if (!IsLinked())
    {
        return false;
    }

	return false;
}

void Shader::unLoad()
{
    glDeleteProgram(shader_program_);
    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
}

void Shader::SetActive()
{
    // 렌더링 파이프라인 실행전 사용할 쉐이더 프로그램 선택
    glUseProgram(shader_program_);
}

void Shader::SetUniformInt(const char* name, int value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniform1d(loc, value);
}

void Shader::SetUniformFloat(const char* name, float value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniform1f(loc, value);
}

void Shader::SetUniformVec2(const char* name, const glm::vec2& value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniform2f(loc, value.x, value.y);
}

void Shader::SetUniformVec3(const char* name, const glm::vec3& value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::SetUniformMat3(const char* name, const glm::mat3& value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& value)
{
    GLuint loc = glGetUniformLocation(shader_program_, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

bool Shader::CompileShader(const char* fileName, GLenum shaderType, GLenum& shader)
{
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contentsStr = sstream.str();
        const char* contentsChar = contentsStr.c_str();

        // 쉐이더를 생성한다.
        shader = glCreateShader(shaderType);
        // 쉐이더에 쉐이더 코드를 등록
        glShaderSource(shader, 1, &contentsChar, nullptr);
        // 쉐이더 컴파일
        glCompileShader(shader);

        return IsCompiled(shader);
    }
    else
    {
        std::cout << "File Is Not Found" << '\n';
    }
    return false;
}

bool Shader::IsCompiled(GLenum shader)
{
    // 컴파일 정상적인 완료 체크
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        std::cout << "Shader Compile Failed : " << buffer << '\n';
        assert(-1);
        return false;
    }

	return true;
}

bool Shader::IsLinked()
{
    GLint status;
    glGetProgramiv(shader_program_, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(shader_program_, 512, nullptr, buffer);
        std::cout << "Shader Program Link Failed : " << buffer << '\n';
        assert(-1);
        return false;
    }

    return true;
}
