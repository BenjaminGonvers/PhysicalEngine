#include <CircleBody.h>


CircleBody::CircleBody(float x, float y)
{
	_position = Vector2(x-10, y-10);
	_velocity = Vector2(0, 0);
	_diameter = 20.0f;
}

CircleBody::CircleBody(float x, float y,float diameter)
{
	_position = Vector2(x - diameter/2, y - diameter/2);
	_velocity = Vector2(0, 0);
	_diameter = diameter;
	_shape = sf::CircleShape(_diameter);
}

CircleBody::CircleBody(sf::Vector2i SfmlVector, float diameter)
{
	_position = Vector2( SfmlVector.x- diameter / 2, -SfmlVector.y - diameter / 2);
	_velocity = Vector2(0, 0);
	_diameter = diameter;
	_shape = sf::CircleShape(_diameter);
}

void CircleBody::draw(sf::RenderWindow& window)
{
	_shape.setFillColor(sf::Color::Blue);
	_shape.setPosition(_position.sfmlVector2().x, _position.sfmlVector2().y);
	window.draw(_shape);

}
