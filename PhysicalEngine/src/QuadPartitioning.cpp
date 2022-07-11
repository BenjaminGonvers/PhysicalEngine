#include <QuadPartitioning.h>


QuadPartitioning::QuadPartitioning(std::vector<std::unique_ptr<RigidBody>>& entity) :
	_entity(entity), _potentialCollision(std::vector<std::pair<RigidBody*, RigidBody*>>())
	, _childNode(std::vector<std::unique_ptr<PartitioningNode>>())
{

}


QuadPartitioning::~QuadPartitioning()
{

}

std::vector<std::pair<RigidBody*, RigidBody*>> QuadPartitioning::CreateList()
{
	CreateFirstNode();
	CreateTreeNode();

	if (!_childNode.empty())
	{
		for (auto& node : _childNode)
		{
		node->CheckAllPossibleCollision(_potentialCollision, _childNode);
		}
	}
	

	return _potentialCollision;
}

float QuadPartitioning::GetMinX()
{
	std::vector<float> x_list;

	for (auto& RigidBody : _entity)
	{

		x_list.emplace_back(RigidBody->getPosition().x);
	}

	return *std::ranges::min_element(x_list);
}

float QuadPartitioning::GetMinY()
{
	std::vector<float> y_list;

	for (auto& RigidBody : _entity)
	{

		y_list.emplace_back(RigidBody->getPosition().y);
	}

	return *std::ranges::min_element(y_list);
}

float QuadPartitioning::GetMaxX()
{
	std::vector<float> x_list;

	for (auto& RigidBody : _entity)
	{

		x_list.emplace_back(RigidBody->getPosition().x);
	}

	return *std::ranges::max_element(x_list);
}

float QuadPartitioning::GetMaxY()
{
	std::vector<float> y_list;

	for (auto& RigidBody : _entity)
	{

		y_list.emplace_back(RigidBody->getPosition().y);
	}

	return *std::ranges::max_element(y_list);
}

void QuadPartitioning::CreateNode()
{
	CreateFirstNode();
	CreateTreeNode();
}

void QuadPartitioning::CreateFirstNode()
{


	for (float itX = std::floor(GetMinX()); itX <= std::ceil(GetMaxX()); itX += 500)
	{
		for (float itY = std::floor(GetMinY()); itY <= std::ceil(GetMaxY()); itY += 500)
		{
			_childNode.emplace_back(std::make_unique<PartitioningNode>(itX, itY, Vector2(500, 500),0));

		}
	}
	
}

void QuadPartitioning::CreateTreeNode()
{
	for (auto& node : _childNode)
	{
		node->CreateNode(_entity);
	}

}


void QuadPartitioning::DebugDraw(sf::RenderWindow& window)
{
	for (auto& node : _childNode)
	{
		node->DebugDraw(window);
	}

}