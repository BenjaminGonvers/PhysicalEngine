#pragma once
#include <RigidBody.h>

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

};

