#include "CubeActor.h"
#include "MeshComponent.h"

CubeActor::CubeActor()
{
	mesh_comp_ = new MeshComponent(this, "Assets/base/Cube.obj");
}

CubeActor::~CubeActor()
{
	Destory();
}
