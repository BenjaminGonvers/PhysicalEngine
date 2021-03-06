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

CircleBody::CircleBody(sf::Vector2f SfmlVector, float diameter)
{
	_position = Vector2( SfmlVector.x, 1000 -SfmlVector.y);
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
	
	_shape.setPosition(_position.x - _diameter/2, 1000 - _position.y - _diameter/2);
	window.draw(_shape);

	

}
