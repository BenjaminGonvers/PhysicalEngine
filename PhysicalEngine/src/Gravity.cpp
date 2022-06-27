#pragma once
#include <Gravity.h>

Gravity::Gravity()
{
	_gravity = Vector2(0,-9.81f);
	_gravityValue = _gravity.magnitude();
}


Gravity::Gravity(Vector2 Gravity)
{
	_gravity = Gravity;
	_gravityValue = _gravity.magnitude();
}


Gravity::~Gravity()
{
}

void Gravity::SetGravity(Vector2 Gravity)
{
	_gravity = Gravity;
	_gravityValue = _gravity.magnitude();
}
void Gravity::Update(std::vector<std::unique_ptr<RigidBody>>& entity)
{
	for (auto&& rigid_body : entity)
	{
		if (rigid_body->AffectedByGravity())
		{
			rigid_body->addVelocity(GivenVelocity());
		}
	}

}

Vector2 Gravity::GivenVelocity()
{
	return _gravity * deltaTime;
}