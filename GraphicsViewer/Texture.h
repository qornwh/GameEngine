#pragma once
#include <string>

class Shader;

class ImageLoad
{
public:
	ImageLoad();
	~ImageLoad();

	unsigned char* ReadImage(const std::string& fileName, int* width, int* height, int* nrChannels);
private:
};

enum TextureType
{
	NONE = 0,
	DIFFUSE = 1,
	METALNESS = 2,
	ROUGHNESS = 3,
	NOMAL = 4,
	AO = 5,
	EMISSIVE = 6,
};

class Texture
{
public:
	Texture();
	~Texture();
	Texture(const Texture& other);
	Texture(Texture&& other) noexcept;

	Texture& operator=(const Texture& other);
	Texture& operator=(Texture&& other) noexcept;

	void SetActive(Shader& shader);
	bool Load(const std::string& fileName);
	void Unload();

	unsigned int GetId() const { return texture_; }
	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }

	void SetType(int type);
	int GetType() { return type_; }
private:
	unsigned int texture_;
	int width_;
	int height_;
	int type_;
};

