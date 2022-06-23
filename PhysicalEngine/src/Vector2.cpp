#pragma once
#include <Vector2.h>
#include <cmath>

Vector2::Vector2()
{
	_x = 0;
	_y = 0;
}

Vector2::Vector2(const float x, const float y)
{
	_x = x;
	_y = y;
}


Vector2::~Vector2()
{

}

Vector2 Vector2::normalized()
{
	return *this / magnitude();
}

float Vector2::magnitude()
{
	return hypot(_x, _y);
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(_x + other._x, _y + other._y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(_x - other._x, _y - other._y);
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
	return Vector2(_x * scalar, _y * scalar);
}

Vector2 Vector2::operator/(const float scalar)
{
	return Vector2(_x / scalar, _y / scalar);
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


