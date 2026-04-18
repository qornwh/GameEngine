#pragma once
#include "Singleton.h"
#include <GLFW/glfw3.h>

class KeyBoardInput : public Singleton<KeyBoardInput>
{
public:
	KeyBoardInput();
	~KeyBoardInput();

	void SetKey(int code, bool action);
	bool GetKey(int code) const { return keys_[code]; }

private:
	bool keys_[GLFW_KEY_LAST + 1];
};

