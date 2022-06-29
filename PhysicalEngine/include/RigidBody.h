#pragma once
#include"Vector2.h"
#include <SFML/Graphics.hpp>

class RigidBody
{
private:
	sf::CircleShape _shape = sf::CircleShape(10.0f);
protected:

	Vector2 _position;
	Vector2 _velocity;
	bool _affectedByGravity = false;
	bool _isCollided = false;

public:

	RigidBody();
	RigidBody(const float x, const float y);
	RigidBody(sf::Vector2i SfmlVector);
	~RigidBody();

	bool AffectedByGravity() const
	{return _affectedByGravity; }
	void AffectedByGravity(bool affected_by_gravity)
	{_affectedByGravity = affected_by_gravity;}

	Vector2 getPosition()
	{return _position;}
	void setPosition(Vector2 newPosition)
	{_position = newPosition;}

	bool IsCollided()
	{return _isCollided;}
	void IsCollided(bool isCollided)
	{_isCollided = isCollided;}

	void addVelocity(Vector2);

	void update(float);
	virtual void draw(sf::RenderWindow&);

};
