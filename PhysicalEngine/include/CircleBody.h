#pragma once
#include <RigidBody.h>

#include "RigidBody.h"



class CircleBody : public RigidBody
{
private:
	sf::CircleShape _shape;
	float _diameter;
public:

	CircleBody(float, float);
	CircleBody(float, float,float);
	CircleBody(sf::Vector2i SfmlVector, float diameter);

	void draw(sf::RenderWindow&) override;

	float getDiameter() const
	{return _diameter;}

	void setDiameter(float newDiameter)
	{_shape.setRadius(newDiameter/2); _diameter = newDiameter;}

};

