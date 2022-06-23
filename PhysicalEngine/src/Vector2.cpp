#pragma once
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
{

}

Vector2 Vector2::sfmlVector2()
{
	return Vector2(x, -y);
}

Vector2 Vector2::normalized()
{
	return *this / magnitude();
}

float Vector2::magnitude()
{
	return hypot(x, y);
}

Vector2 Vector2::rightOrthogonal()
{
	return Vector2(y, -x);
}

Vector2 Vector2::leftOrthogonal()
{
	return Vector2(-y, x);
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
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

Vector2 Vector2::operator*(const float scalar)
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(const float scalar)
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


//dotProduct = V1.x * V2.x + V1.y * V2.y
