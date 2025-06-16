#pragma once
#include <string>

class ImageLoad
{
public:
	ImageLoad();
	~ImageLoad();

	unsigned char* ReadImage(const std::string& fileName, int* width, int* height, int* nrChannels);
private:
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

	void SetActive(int number = 0);
	bool Load(const std::string& fileName);
	void Unload();

	unsigned int GetId() const { return texture_; }
	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }
private:
	unsigned int texture_;
	int width_;
	int height_;
};

