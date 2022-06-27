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
	_position = Vector2(x-10, y-10);
	_velocity = Vector2(0, 0);
}

RigidBody::RigidBody(sf::Vector2i SfmlVector)
{
	_position = Vector2(SfmlVector.x-10, - SfmlVector.y - 10.0f);
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
	_shape.setFillColor(sf::Color::Red);
	_shape.setPosition(_position.sfmlVector2().x, _position.sfmlVector2().y);
	window.draw(_shape);
}