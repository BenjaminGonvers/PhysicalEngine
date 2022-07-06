#pragma once
#include <RigidBody.h>

class RectangleBody : public RigidBody
{
private:
	sf::RectangleShape _shape;
	Vector2 _a;
	Vector2 _b;
	Vector2 _c;
	Vector2 _d;

public:
	RectangleBody(float, float, float, float);
	RectangleBody(sf::Vector2f, float, float);
	~RectangleBody();

	Vector2 a() { return _a; }
	void a(Vector2 pointA) { _a = pointA; }

	Vector2 b() { return _b; }
	void b(Vector2 pointB) { _b = pointB; }

	Vector2 c() { return _c; }
	void c(Vector2 pointC) { _c = pointC; }

	Vector2 d() { return _d; }
	void d(Vector2 pointD) { _d = pointD; }

	Vector2 aRelative() { return  _position + _a; }
	void aRelative(Vector2 pointA) { _a = pointA - _position; }

	Vector2 bRelative() { return _position + _b; }
	void bRelative(Vector2 pointB) { _b = pointB-_position; }

	Vector2 cRelative() { return  _position + _c; }
	void cRelative(Vector2 pointC) { _c = pointC - _position; }

	Vector2 dRelative() { return  _position + _d; }
	void dRelative(Vector2 pointD) { _d = pointD - _position; }


	void draw(sf::RenderWindow&) override;
};

