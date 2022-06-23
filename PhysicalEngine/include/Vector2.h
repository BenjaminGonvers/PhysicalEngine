#pragma once

class Vector2
{
private:

	float _x;
	float _y;

public:

	Vector2();
	Vector2(float x, float y);
	~Vector2();
	
	float magnitude();
	Vector2 normalized();

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);

	Vector2 operator*(const float scalar);
	Vector2 operator/(const float scalar);

	Vector2 operator*=(const float scalar);
	Vector2 operator/=(const float scalar);

};