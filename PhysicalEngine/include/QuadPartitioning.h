#pragma once
#include <vector>
#include <RigidBody.h>
#include <PartitioningNode.h>
#include <Vector2.h>

class QuadPartitioning
{
public:

	QuadPartitioning(std::vector<std::unique_ptr<RigidBody>>&);
	~QuadPartitioning();

	
	std::vector<std::pair<RigidBody*, RigidBody*>> CreateList();

	float GetMinX();
	float GetMinY();
	float GetMaxX();
	float GetMaxY();
	void CreateNode();

	void CreateFirstNode();
	void CreateTreeNode();

	void DebugDraw(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<RigidBody>>& _entity;
	std::vector<std::pair<RigidBody*, RigidBody*>> _potentialCollision;

	std::vector<std::unique_ptr<PartitioningNode>> _childNode;

};

