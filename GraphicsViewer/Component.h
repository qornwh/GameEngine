#pragma once

class Actor;

class Component
{
public:
	Component(Actor* actor, int order = 0);
	~Component();

	// 프레임 업데이트
	virtual void Update(float deltaTime) {};
	// 액터의 월드 좌표 변경시 업데이트
	virtual void OnUpdateWorldTransform() {};
	// 인풋 액션

	virtual void Remove() {};

	Actor* GetActor() { return actor_; }
	int GetOrder() { return order_; }
private:
	Actor* actor_;
	int order_;
};

