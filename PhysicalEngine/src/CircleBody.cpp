#include <CircleBody.h>


CircleBody::CircleBody(float x, float y)
{
	_position = Vector2(x, y);
	_velocity = Vector2(0, 0);
	_diameter = 20.0f;
}

CircleBody::CircleBody(float x, float y,float diameter)
{
	_position = Vector2(x, y);
	_velocity = Vector2(0, 0);
	_diameter = diameter;
	_shape = sf::CircleShape(_diameter/2);
}

CircleBody::CircleBody(sf::Vector2i SfmlVector, float diameter)
{
	_position = Vector2( SfmlVector.x, -SfmlVector.y);
	_velocity = Vector2(0, 0);
	_diameter = diameter;
	_shape = sf::CircleShape(_diameter/2);
}

void CircleBody::draw(sf::RenderWindow& window)
{
	if(_isCollided)
	{_shape.setFillColor(sf::Color::Red);
	}else
	{_shape.setFillColor(sf::Color::Blue);}
	
	_shape.setPosition(_position.sfmlVector2().x - _diameter/2, _position.sfmlVector2().y - _diameter/2);
	window.draw(_shape);

}
