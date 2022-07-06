#include <RectangleBody.h>

RectangleBody::RectangleBody(float posX,float posY,float length, float width) :_shape(sf::Vector2f(length, width))
{
	_a = Vector2(-length / 2, width / 2);
	_b = Vector2(length / 2, width / 2);
	_c = Vector2(length / 2, -width / 2);
	_d = Vector2(-length / 2, -width / 2);
	_position = Vector2(posX, -posY);
	_shape.setOrigin(length / 2, width / 2);
}

RectangleBody::RectangleBody(sf::Vector2f position, float length, float width) :_shape(sf::Vector2f(length, width))
{
	_a = Vector2(-length / 2, width / 2);
	_b = Vector2(length / 2, width / 2);
	_c = Vector2(length / 2, -width / 2);
	_d = Vector2(-length / 2, -width / 2);
	_position = Vector2(position.x,-position.y);
	_shape.setOrigin(length / 2, width / 2);
}


RectangleBody::~RectangleBody()
= default;

void RectangleBody::draw(sf::RenderWindow& window)
{

	if (_isCollided)
	{
		_shape.setFillColor(sf::Color::Red);
	}
	else
	{
		_shape.setFillColor(sf::Color::Blue);
	}

	_shape.setPosition(_position.sfmlVector2());
	window.draw(_shape);

	sf::ConvexShape shape;
	shape.setPointCount(3);
	shape.setPoint(0, _position.sfmlVector2());
	shape.setPoint(1, (_position + Vector2(0, _velocity.y)).sfmlVector2());
	shape.setPoint(2, (_position + Vector2(_velocity.x, 0)).sfmlVector2());
	shape.setFillColor(sf::Color::Yellow);
	window.draw(shape);
}