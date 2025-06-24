#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include <iostream>
#include <assimp/material.h>
#include "Shader.h"

ImageLoad::ImageLoad()
{
}

ImageLoad::~ImageLoad()
{
}

unsigned char* ImageLoad::ReadImage(const std::string& fileName, int* width, int* height, int* nrChannels)
{
	stbi_set_flip_vertically_on_load(true);
	return stbi_load(fileName.c_str(), width, height, nrChannels, 0);
}

Texture::Texture() : texture_(0), width_(0), height_(0), type_(0)
{
}

Texture::~Texture()
{
	Unload();
}

Texture::Texture(const Texture& other)
{
	texture_ = other.texture_;
	width_ = other.width_;
	height_ = other.height_;
	type_ = other.type_;
}

Texture::Texture(Texture&& other) noexcept
{
	texture_ = other.texture_;
	width_ = other.width_;
	height_ = other.height_;
	type_ = other.type_;
}

Texture& Texture::operator=(const Texture& other)
{
	texture_ = other.texture_;
	width_ = other.width_;
	height_ = other.height_;
	type_ = other.type_;
	return *this;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	texture_ = other.texture_;
	width_ = other.width_;
	height_ = other.height_;
	type_ = other.type_;
	return *this;
}

bool Texture::Load(const std::string& fileName)
{
	ImageLoad il;
	int channel;
	unsigned char* img = il.ReadImage(fileName, &width_, &height_, &channel);

	if (img == nullptr)
	{
		std::cout << "Texture2D Image Load Failed!\n";
		return false;
	}

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	GLenum format = GL_RGB;
	if (channel == 1)
	{
		format = GL_RED;
	}
	else if (channel == 2)
	{
		format = GL_RG;
	}
	else if (channel == 4)
	{
		format = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(img);
	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &texture_);
}

void Texture::SetType(int type)
{
	type_ = type;
}

void Texture::SetActive(Shader& shader)
{
	glBindTexture(GL_TEXTURE_2D, texture_);
}
