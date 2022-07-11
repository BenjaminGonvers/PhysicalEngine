#pragma once
#include <vector>

#include "CircleBody.h"
#include "RigidBody.h"

class CollisionChecker
{
public:
	CollisionChecker();
	~CollisionChecker();
	std::vector<std::pair<RigidBody*, RigidBody*>> CreateList(
		std::vector<std::pair<RigidBody*, RigidBody*>> listToCheck);
	void emplaceInVectorCollision(RigidBody* , RigidBody* );
	bool IsCollindingCorner(CircleBody* circleBody, Vector2 corner);

private:
	std::vector<std::pair<RigidBody*, RigidBody*>> _vectorCollision;
};
