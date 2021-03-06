#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include <RigidBody.h>

class PartitioningNode
{
public:
	PartitioningNode(Vector2 position, Vector2 size,int);
	PartitioningNode(float posX, float posY, Vector2 size,int);
	~PartitioningNode();

	void CreateNode(std::vector<std::unique_ptr<RigidBody>>& possibleObject);
	void CreateNode(std::vector<RigidBody*>& possibleObject);
	void CheckAllPossibleCollision(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision,
	                               std::vector<std::unique_ptr<PartitioningNode>>& firstChildNode);
	void CheckPossibleCollision(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision,
	                            PartitioningNode* nodeToCheck);
	void CheckPossibleCollisionInbound(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision);
	void DebugDraw(sf::RenderWindow& window);
	int GetNumberObject() const;


private:
	
	std::vector<std::unique_ptr<PartitioningNode>> _childNode;
	std::vector<RigidBody*> _entityInBound;

	Vector2 _position;
	Vector2 _size;

	int _actualDeep;
};
