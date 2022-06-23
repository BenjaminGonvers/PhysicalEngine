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

public:

	RigidBody();
	RigidBody(const float x, const float y);
	RigidBody(sf::Vector2i SfmlVector);
	~RigidBody();

	void update();
	virtual void draw(sf::RenderWindow&);

};
