#pragma once
#include "RigidBody.h"

class GameObject
{
private:


	RigidBody _rigidBody;

public:

	GameObject();
	~GameObject();

	void Update();

};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

inline void GameObject::Update()
{
}
