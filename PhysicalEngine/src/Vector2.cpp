#include "SFML/System/Vector2.hpp"

#include <Vector2.h>
#include <cmath>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
= default;

sf::Vector2f Vector2::sfmlVector2()
{
	return {x, -y};
}

Vector2 Vector2::normalized() const
{
	return *this / magnitude();
}

float Vector2::magnitude() const
{
	return hypot(x, y);
}

Vector2 Vector2::rightOrthogonal() const
{
	return Vector2(y, -x);
}

Vector2 Vector2::leftOrthogonal() const
{
	return Vector2(-y, x);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	*this = *this + other;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	*this = *this - other;
	return *this;
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2 Vector2::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}

bool Vector2::operator<(const Vector2& other) const
{
	if(y<other.y&&x<other.x)
	{
		return true;
	}
	return false;
}

bool Vector2::operator>(const Vector2& other) const
{
	if (y > other.y && x > other.x)
	{
		return true;
	}
	return false;
}

bool Vector2::operator==(const Vector2& other) const
{
	if (y == other.y && x == other.x)
	{
		return true;
	}
	return false;
}

float Vector2::GetAngularToOAxisX() const
{
	return std::atan2(y,x);
}

float Vector2::DotProduct(const Vector2& otherVector) const
{
	return x * otherVector.x + y * otherVector.y;
}


float Vector2::GetAngularToVector(const Vector2 other) const
{
	return std::atan2(y, x) - std::atan2(other.y, other.x);
}
