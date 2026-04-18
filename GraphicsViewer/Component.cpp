#include "Component.h"
#include "Actor.h"

Component::Component(Actor* actor, int order) : actor_(actor), order_(order)
{
}

Component::~Component()
{
}
