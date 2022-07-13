#pragma once
#include <vector>
#include <RigidBody.h>


class Gravity
{
private:
	
	Vector2 _gravity;
	float _gravityValue;


public:

	float deltaTime = 0;
	Gravity();
	Gravity(const Vector2&);
	Gravity(float Gravity);
	~Gravity();

	void SetGravity(Vector2);
	Vector2 GivenVelocity();

	void Update(std::vector<std::unique_ptr<RigidBody>>&);

};