#include <PartitioningNode.h>

PartitioningNode::PartitioningNode(Vector2 position, Vector2 size,int deep) :
	_childNode(std::vector<std::unique_ptr<PartitioningNode>>())
{
	_position = position;
	_size = size;
	_actualDeep = deep + 1;
}


PartitioningNode::PartitioningNode(float posX, float posY, Vector2 size,int deep) :
	_childNode(std::vector<std::unique_ptr<PartitioningNode>>())
{
	_position = Vector2(posX, posY);
	_size = size;
	_actualDeep = deep + 1;
}

PartitioningNode::~PartitioningNode()
{
}

void PartitioningNode::CreateNode(std::vector<std::unique_ptr<RigidBody>>& possibleObject)
{
	if(!possibleObject.empty())
	{
		for (auto& rigidBody : possibleObject)
		{
			if (rigidBody->getPosition() <= _position + _size && rigidBody->getPosition() >= _position)
			{
				_entityInBound.emplace_back(rigidBody.get());
			}

		}
	}
	

	if (_entityInBound.size() >= 5 && _actualDeep < 4 )
	{
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position, _size / 2,_actualDeep));//1
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x,_position.y + _size.y / 2, _size / 2, _actualDeep));//2
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x/2, _position.y, _size / 2, _actualDeep));//3
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x/2, _position.y + _size.y/2, _size / 2, _actualDeep));//4
		 
		for (auto& node : _childNode)
		{
			node->CreateNode(_entityInBound);
		}
	}

	
}

void PartitioningNode::CreateNode(std::vector<RigidBody*>& possibleObject)
{
	if (!possibleObject.empty())
	{
		for (auto& rigidBody : possibleObject)
		{
			if (rigidBody->getPosition() <= _position + _size && rigidBody->getPosition() >= _position)
			{
				_entityInBound.emplace_back(rigidBody);
			}

		}
	}

	if (_entityInBound.size() >= 5 && _actualDeep < 4)
	{
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position, _size / 2, _actualDeep));//1
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x, _position.y + _size.y / 2, _size / 2, _actualDeep));//2
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x / 2, _position.y, _size / 2, _actualDeep));//3
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x / 2, _position.y + _size.y / 2, _size / 2, _actualDeep));//4

		for (auto& Node : _childNode)
		{
			Node->CreateNode(_entityInBound);
		}

	}

	
}

void PartitioningNode::CheckAllPossibleCollision(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision,std::vector<std::unique_ptr<PartitioningNode>>& firstChildNode)
{
	if(_childNode.empty())
	{
		for (auto& node : firstChildNode)
		{
		node->CheckPossibleCollision(potentialCollision, this);
		}
	}else
	{
		for (auto& node : _childNode)
		{
			node->CheckAllPossibleCollision(potentialCollision, firstChildNode);
		}
	}
	
	
}

void PartitioningNode::CheckPossibleCollision(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision, PartitioningNode* nodeToCheck)
{
	if(nodeToCheck->_position <= _position + _size && nodeToCheck->_position + nodeToCheck->_size>= _position)
	{
		if(!_childNode.empty())
		{
			for (auto& node : _childNode)
			{
				node->CheckPossibleCollision(potentialCollision, nodeToCheck);
			}
			
		}else
		{
			for (auto& i : nodeToCheck->_entityInBound)
			{
				for (auto& it : _entityInBound)
				{
					if(i != it)
					{
						potentialCollision.emplace_back(i, it);
					}
				}
			}
		}

	}

}

void PartitioningNode::CheckPossibleCollisionInbound(std::vector<std::pair<RigidBody*, RigidBody*>>& potentialCollision)
{
	if(_entityInBound.size()>=2)
	{
		for (int i = 0; i+1 < _entityInBound.size();i++)
		{
			for(int it = i+1;it < _entityInBound.size();it++)
			{
				potentialCollision.emplace_back(std::pair(_entityInBound[i], _entityInBound[it]));
			}
		}
	}
}

void PartitioningNode::DebugDraw(sf::RenderWindow& window)
{
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2(_size.x, _size.y));
	shape.setPosition(_position.x,1000-_position.y);
	shape.setOrigin(0, +_size.y);
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(2);
	window.draw(shape);


	for (auto& node : _childNode)
	{
		node->DebugDraw(window);
	}

}

int PartitioningNode::GetNumberObject() const
{
	return _entityInBound.size();
}
