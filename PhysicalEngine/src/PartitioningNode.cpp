#include <PartitioningNode.h>

PartitioningNode::PartitioningNode(Vector2 position, Vector2 size) :
	_childNode(std::vector<std::unique_ptr<PartitioningNode>>())
{
	_position = position;
	_size = size;
}


PartitioningNode::PartitioningNode(float posX, float posY, Vector2 size) :
	_childNode(std::vector<std::unique_ptr<PartitioningNode>>())
{
	_position = Vector2(posX, posY);
	_size = size;

}

PartitioningNode::~PartitioningNode()
{
}

void PartitioningNode::CreateNode(std::vector<std::unique_ptr<RigidBody>>& possibleObject)
{
	for (auto& rigidBody : possibleObject)
	{
		if (rigidBody->getPosition().x > _position.x && rigidBody->getPosition().y < _position.y &&
			rigidBody->getPosition().x < _position.x + _size.x && rigidBody->getPosition().y > _position.y - _size.y)
		{
			_entityInBound.emplace_back(rigidBody.get());
		}

	}

	if (_entityInBound.size() >= 5)
	{
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x,_position.y- _size.y/2, _size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x,_position.y,_size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x/2, _position.y-_size.y/2, _size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x+ _size.x/2, _position.y, _size / 2));
	}

	for (auto& Node : _childNode)
	{
		Node->CreateNode(_entityInBound);
	}
}

void PartitioningNode::CreateNode(std::vector<RigidBody*>& possibleObject)
{
	for (auto& rigidBody : possibleObject)
	{
		if (rigidBody->getPosition().x > _position.x && rigidBody->getPosition().y < _position.y &&
			rigidBody->getPosition().x < _position.x + _size.x && rigidBody->getPosition().y > _position.y - _size.y)
		{
			_entityInBound.emplace_back(rigidBody);
		}

	}

	if (_entityInBound.size() >= 5)
	{
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x, _position.y - _size.y / 2, _size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x, _position.y, _size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x / 2, _position.y - _size.y / 2, _size / 2));
		_childNode.emplace_back(std::make_unique<PartitioningNode>(_position.x + _size.x / 2, _position.y, _size / 2));
	}

	for (auto& Node : _childNode)
	{
		Node->CreateNode(_entityInBound);
	}
}

void PartitioningNode::DebugDraw(sf::RenderWindow& window)
{
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2(_size.x, _size.y));
	shape.setPosition(_position.sfmlVector2().x,_position.sfmlVector2().y);
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(5);
	window.draw(shape);
	sf::Text text = sf::Text();
	text.setString(std::to_string(_position.y));
	text.setPosition(_position.sfmlVector2());
	text.setColor(sf::Color::White);
	window.draw(text);


	for (auto& node : _childNode)
	{
		node->DebugDraw(window);
	}

}