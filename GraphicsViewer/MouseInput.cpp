#include "MouseInput.h"

MouseInput::MouseInput() : x_(0), y_(0), left_(MouseState::NONE), right_(MouseState::NONE), wheel_(MouseState::NONE)
{
}

MouseInput::~MouseInput()
{
}

void MouseInput::SetX(int x)
{
	pre_x_ = x_;
	x_ = x;
}

void MouseInput::SetY(int y)
{
	pre_y_ = y_;
	y_ = y;
}

void MouseInput::SetLeft(int state)
{
	UpdateState(left_, state);
}

void MouseInput::SetRight(int state)
{
	UpdateState(right_, state);
}

void MouseInput::SetWheel(int state)
{
	UpdateState(wheel_, state);
}

void MouseInput::SetScrollX(int offset)
{
	scroll_offset_x_ = offset;
}

void MouseInput::SetScrollY(int offset)
{
	scroll_offset_y_ = offset;
}

void MouseInput::Update()
{
}

void MouseInput::UpdateState(MouseState& mouseState, int state)
{
	if (static_cast<int>(MouseState::DOWN) == state)
	{
		mouseState = MouseState::DOWN;
	}
	else if (static_cast<int>(MouseState::UP) == state)
	{
		mouseState = MouseState::UP;
	}
	else
	{
		mouseState = MouseState::NONE;
	}
}
