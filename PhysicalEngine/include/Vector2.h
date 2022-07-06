#pragma once
#include "SFML/System/Vector2.hpp"

class Vector2
{

public:

	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	~Vector2();
	
	float magnitude() const;
	Vector2 normalized() const;

	sf::Vector2f sfmlVector2();

	Vector2 rightOrthogonal() const;
	Vector2 leftOrthogonal() const;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);

	Vector2 operator*(const float scalar) const;
	Vector2 operator/(const float scalar) const;

	Vector2 operator*=(const float scalar);
	Vector2 operator/=(const float scalar);

	float GetAngularToOAxisX() const;
	float DotProduct(const Vector2&) const;
	float GetAngularToVector(const Vector2) const;
};