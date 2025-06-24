#pragma once
#include "Actor.h"

class MeshComponent;

class CubeActor : public Actor
{
public:
	// 큐브 메시
	CubeActor();
	~CubeActor();
private:
	MeshComponent* mesh_comp_;
};

