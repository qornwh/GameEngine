#pragma once
#include "Texture.h"

class ShadowFBO
{
public:
	ShadowFBO();
	~ShadowFBO();

	void Init();
	void SetActive();

	unsigned int GetFBO() { return frameBuffer_; }
	unsigned int GetTexture() { return texture_; }

private:
	unsigned int frameBuffer_;
	unsigned int texture_;

	int SHADOW_WIDTH = 2048;
	int SHADOW_HEIGHT = 2048;
};

