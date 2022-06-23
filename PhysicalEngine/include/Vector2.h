#pragma once

class Vector2
{

public:

	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	~Vector2();
	
	float magnitude();
	Vector2 normalized();
	Vector2 sfmlVector2();

	Vector2 rightOrthogonal();
	Vector2 leftOrthogonal();

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);

	Vector2 operator*(const float scalar);
	Vector2 operator/(const float scalar);

	Vector2 operator*=(const float scalar);
	Vector2 operator/=(const float scalar);

};