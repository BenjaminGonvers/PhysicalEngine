#pragma once
#include <vector>

#include "CircleBody.h"
#include "RigidBody.h"

class CollisionChecker
{
public:
	CollisionChecker(std::vector<std::unique_ptr<RigidBody>>&);
	~CollisionChecker();
	std::vector<std::pair<RigidBody*, RigidBody*>> CreateList();
	void emplaceInVectorCollision(RigidBody* , RigidBody* );
	bool IsCollindingCorner(CircleBody* circleBody, Vector2 corner);

private:
	std::vector<std::unique_ptr<RigidBody>>& _listToCheck;
	std::vector<std::pair<RigidBody*, RigidBody*>> _vectorCollision;
};
