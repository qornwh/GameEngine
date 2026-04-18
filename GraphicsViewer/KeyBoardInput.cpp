#include "KeyBoardInput.h"
#include <memory>

KeyBoardInput::KeyBoardInput()
{
	memset(&keys_[0], false, GLFW_KEY_LAST + 1);
}

KeyBoardInput::~KeyBoardInput()
{
}

void KeyBoardInput::SetKey(int code, bool action)
{
	keys_[code] = action;
}
