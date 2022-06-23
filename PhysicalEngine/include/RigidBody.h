#pragma once
#include"Vector2.h"

class RigidBody
{
private:

	Vector2 _position;
	Vector2 _velocity;


Public:

	RigidBody();
	RigidBody(const float x,const float y)
	~RigidBody();

	void Update();


};



RigidBody::RigidBody()
{
	_position(0, 0);
}

RigidBody::RigidBody(const float x,const float y)
{
	_position(x, y);
}

RigidBody::~RigidBody()
{

}

inline void RigidBody::Update()
{

}
