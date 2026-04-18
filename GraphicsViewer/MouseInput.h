#pragma once
#include "Singleton.h"

enum class MouseState
{
	NONE = 0,
	UP = 1,
	DOWN = 2
};

class MouseInput : public Singleton<MouseInput>
{
public:
	MouseInput();
	~MouseInput();

	void SetX(int x);
	void SetY(int y);

	int GetX() const { return x_; }
	int GetY() const { return y_; }

	void SetLeft(int state);
	void SetRight(int state);
	void SetWheel(int state);
	void SetScrollX(int offset);
	void SetScrollY(int offset);

	MouseState GetLeft() const { return left_; }
	MouseState GetRight() const { return right_; }
	MouseState GetWheel() const { return wheel_; }

	int delX() const { return x_ - pre_x_; }
	int delY() const { return pre_y_ - y_; }

	int ScrollOffsetX() const { return scroll_offset_x_; }
	int ScrollOffsetY() const { return scroll_offset_y_; }

	void Update();
 
private:
	int pre_x_ = 0;
	int pre_y_ = 0;
	int x_ = 0;
	int y_ = 0;
	int scroll_offset_x_ = 0;
	int scroll_offset_y_ = 0;
	MouseState left_;
	MouseState right_;
	MouseState wheel_;

	void UpdateState(MouseState& mouseState, int state);
};

