#pragma once
#include <utility>
#include <vector>
#include <CircleBody.h>
#include <Vector2.h>
#include <numbers>

#include "RectangleBody.h"


class CollisionSolver
{
private:
	std::vector<std::pair<RigidBody*, RigidBody*>> _listToSolve;

public:
	CollisionSolver(std::vector<std::pair<RigidBody*, RigidBody*>>);
	~CollisionSolver();

	void SolveCollisionList();
	void ResolveCircleCircle(CircleBody*, CircleBody*);
	void ResolveRectangleRectangle(RectangleBody* FirstRectangleBody, RectangleBody* SegondRectangleBody);
	void ResolveCircleRectangle(CircleBody* FirstRectangleBody, RectangleBody* SegondRectangleBody);
	void ResolveCircleRectangleCorner(CircleBody* circleBody, RectangleBody* rectangleBody, Vector2 corner);
};

