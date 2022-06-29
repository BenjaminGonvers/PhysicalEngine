#include <CollisionChecker.h>

CollisionChecker::CollisionChecker(std::vector<std::unique_ptr<RigidBody>>& listToCheck)
	:_listToCheck(listToCheck), _vectorCollision(std::vector<std::pair<RigidBody*, RigidBody*>>())
{}

CollisionChecker::~CollisionChecker()
{
}

std::vector<std::pair<RigidBody*, RigidBody*>> CollisionChecker::CreateList()
{
	for (auto& i : _listToCheck)
	{
		i->IsCollided(false);
	}

	for (std::size_t i = 0; i+1 < _listToCheck.size(); i++)
	{
		

		for (std::size_t it = i + 1; it < _listToCheck.size(); it++)
		{
			auto* FirstBody = dynamic_cast<CircleBody*>(_listToCheck[i].get());
			auto* SegondBody = dynamic_cast<CircleBody*>(_listToCheck[it].get());

			if (FirstBody != nullptr && SegondBody != nullptr)
			{
				if ((FirstBody->getPosition() - SegondBody->getPosition()).magnitude() <= FirstBody->getDiameter()/2 + SegondBody->getDiameter()/2)
				{
					int alreadyCollide = false;

					for (int ite = 0; ite < _vectorCollision.size(); ite++)
					{
						if (_vectorCollision[ite].first == FirstBody && _vectorCollision[ite].second == SegondBody ||
							_vectorCollision[ite].first == SegondBody && _vectorCollision[ite].second == FirstBody)
						{
							alreadyCollide = true;
						}
					}
					if (!alreadyCollide)
					{
						_vectorCollision.emplace_back(std::pair<RigidBody*, RigidBody*>(FirstBody, SegondBody));
						FirstBody->IsCollided(true);
						SegondBody->IsCollided(true);
					}

				}
			}

		}
	}
	return _vectorCollision;
}