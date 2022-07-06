#pragma once
#include <iostream>
#include <RigidBody.h>

RigidBody::RigidBody()
{
	_affectedByGravity = true;
	_position = Vector2(0, 0);
	_velocity = Vector2(0, 0);
}

RigidBody::RigidBody(const float x, const float y)
{
	_affectedByGravity = true;
	_position = Vector2(x, y);
	_velocity = Vector2(0, 0);
}

RigidBody::RigidBody(sf::Vector2i SfmlVector)
{
	_position = Vector2(SfmlVector.x, - SfmlVector.y);
	_velocity = Vector2(0, 0);
}

RigidBody::~RigidBody()
{

}

void RigidBody::addVelocity(Vector2 otherVelocity)
{
	_velocity += otherVelocity;
}

void RigidBody::update(float deltaTime)
{
	_position += _velocity * deltaTime;
}

void RigidBody::draw(sf::RenderWindow& window)
{
	
}