#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include <RigidBody.h>

class PartitioningNode
{
public:
	PartitioningNode(Vector2 position, Vector2 size);
	PartitioningNode(float posX, float posY, Vector2 size);
	~PartitioningNode();

	void CreateNode(std::vector<std::unique_ptr<RigidBody>>& possibleObject);
	void CreateNode(std::vector<RigidBody*>& possibleObject);
	void DebugDraw(sf::RenderWindow& window);


private:
	std::vector<std::unique_ptr<PartitioningNode>> _childNode;
	std::vector<RigidBody*> _entityInBound;

	Vector2 _position;
	Vector2 _size;

};
