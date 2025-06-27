#pragma once
#include "GameGlobals.h"
#include "Actor.h"

class ActorFactory
{
public:
	template<typename T>
	T* SpawnActor();

	template<typename T>
	T* SpawnActor(Actor* parent);

private:
};

template<typename T>
inline T* ActorFactory::SpawnActor()
{
	return SpawnActor<T>(Game::World()->GetRootActor());
}

template<typename T>
inline T* ActorFactory::SpawnActor(Actor* parent)
{
	assert(parent != nullptr);
	static_assert(std::is_base_of_v<Actor, T>);

	T* actor = new T();
	parent->AddChild(reinterpret_cast<Actor*>(actor));
	return actor;
}
