#pragma once
#include "RigidBody.h"

class GameObject
{
private:

	RigidBody _rigidBody;

public:

	GameObject();
	~GameObject();

};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
