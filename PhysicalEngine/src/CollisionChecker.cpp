#include <CollisionChecker.h>

#include "RectangleBody.h"

CollisionChecker::CollisionChecker()
	: _vectorCollision(std::vector<std::pair<RigidBody*, RigidBody*>>())
{}

CollisionChecker::~CollisionChecker()
{
}

std::vector<std::pair<RigidBody*, RigidBody*>> CollisionChecker::CreateList(std::vector<std::pair<RigidBody*, RigidBody*>> listToCheck)
{
	for (auto& pairRigidBody : listToCheck)
	{
		pairRigidBody.first->IsCollided(false);
		pairRigidBody.second->IsCollided(false);
	}

	for (auto& pairRigidBody : listToCheck)
	{
		auto* firstCircleBody = dynamic_cast<CircleBody*>(pairRigidBody.first);
		auto* segondCircleBody = dynamic_cast<CircleBody*>(pairRigidBody.second);

		if (firstCircleBody != nullptr && segondCircleBody != nullptr)
		{
			if ((firstCircleBody->getPosition() - segondCircleBody->getPosition()).magnitude() <= firstCircleBody->getDiameter()/2 + segondCircleBody->getDiameter()/2)
			{
					emplaceInVectorCollision(firstCircleBody, segondCircleBody);
			}
		}
			
			
		auto* firstRectangleBody = dynamic_cast<RectangleBody*>(pairRigidBody.first);
		auto* segondRectangleBody = dynamic_cast<RectangleBody*>(pairRigidBody.second);

		if ((firstRectangleBody != nullptr) != (segondRectangleBody != nullptr) && (firstCircleBody != nullptr) != (segondCircleBody != nullptr))
		{
			CircleBody* TCircleBody;
			RectangleBody* TRectangleBody;

			if(firstCircleBody != nullptr)
				TCircleBody = firstCircleBody;
			if(segondCircleBody != nullptr)
				TCircleBody = segondCircleBody;

			if(firstRectangleBody != nullptr)
				TRectangleBody = firstRectangleBody;
			if (segondRectangleBody != nullptr)
				TRectangleBody = segondRectangleBody;

			Vector2 distance(abs(TRectangleBody->getPosition().x - TCircleBody->getPosition().x), abs(TRectangleBody->getPosition().y - TCircleBody->getPosition().y));
			if(!(distance.x > abs(TRectangleBody->b().x-TRectangleBody->a().x)/2 + TCircleBody->getDiameter()/2 ||
				distance.y > abs(TRectangleBody->b().y - TRectangleBody->c().y) / 2 + TCircleBody->getDiameter() / 2))
			{
				if(distance.x <= abs(TRectangleBody->b().x - TRectangleBody->a().x) / 2 ||
					distance.y <= abs(TRectangleBody->b().y - TRectangleBody->c().y) / 2)
				{
					emplaceInVectorCollision(TCircleBody, TRectangleBody);
							
				}
				else {
					bool iscollindingcorner = false;
					iscollindingcorner += IsCollindingCorner(TCircleBody, TRectangleBody->aRelative()) + IsCollindingCorner(TCircleBody, TRectangleBody->bRelative())
					+ IsCollindingCorner(TCircleBody, TRectangleBody->cRelative()) + IsCollindingCorner(TCircleBody, TRectangleBody->dRelative());

					if (iscollindingcorner)
					{
						emplaceInVectorCollision(TCircleBody, TRectangleBody);
					}
				}
			}

						
		}

		if (firstRectangleBody != nullptr && segondRectangleBody != nullptr)
		{
			float firstMinX = std::min(std::min(firstRectangleBody->aRelative().x, firstRectangleBody->bRelative().x), std::min(firstRectangleBody->cRelative().x, firstRectangleBody->dRelative().x));
			float segondMinX = std::min(std::min(segondRectangleBody->aRelative().x, segondRectangleBody->bRelative().x), std::min(segondRectangleBody->cRelative().x, segondRectangleBody->dRelative().x));
			float firstMinY = std::min(std::min(firstRectangleBody->aRelative().y, firstRectangleBody->bRelative().y), std::min(firstRectangleBody->cRelative().y, firstRectangleBody->dRelative().y));
			float segondMinY = std::min(std::min(segondRectangleBody->aRelative().y, segondRectangleBody->bRelative().y), std::min(segondRectangleBody->cRelative().y, segondRectangleBody->dRelative().y));

			float firstMaxX = std::max(std::max(firstRectangleBody->aRelative().x, firstRectangleBody->bRelative().x), std::max(firstRectangleBody->cRelative().x, firstRectangleBody->dRelative().x));
			float segondMaxX = std::max(std::max(segondRectangleBody->aRelative().x, segondRectangleBody->bRelative().x), std::max(segondRectangleBody->cRelative().x, segondRectangleBody->dRelative().x));
			float firstMaxY = std::max(std::max(firstRectangleBody->aRelative().y, firstRectangleBody->bRelative().y), std::max(firstRectangleBody->cRelative().y, firstRectangleBody->dRelative().y));
			float segondMaxY = std::max(std::max(segondRectangleBody->aRelative().y, segondRectangleBody->bRelative().y), std::max(segondRectangleBody->cRelative().y, segondRectangleBody->dRelative().y));

			if (firstMaxX >= segondMinX && firstMinX <= segondMaxX && firstMinY <= segondMaxY && firstMaxY >= segondMinY)
			{
				emplaceInVectorCollision(firstRectangleBody, segondRectangleBody);
			}

				
		}
	}
	
	return _vectorCollision;
}

void CollisionChecker::emplaceInVectorCollision(RigidBody* firstBody ,RigidBody* segondBody)
{

	int alreadyCollide = false;

	for (int ite = 0; ite < _vectorCollision.size(); ite++)
	{
		if (_vectorCollision[ite].first == firstBody && _vectorCollision[ite].second == segondBody ||
			_vectorCollision[ite].first == segondBody && _vectorCollision[ite].second == firstBody)
		{
			alreadyCollide = true;
		}
	}
	if (!alreadyCollide)
	{
		_vectorCollision.emplace_back(std::pair<RigidBody*, RigidBody*>(firstBody, segondBody));
		firstBody->IsCollided(true);
		segondBody->IsCollided(true);
	}


}

bool CollisionChecker::IsCollindingCorner(CircleBody* circleBody,Vector2 corner)
{
	if ((corner - circleBody->getPosition()).magnitude() <= circleBody->getDiameter() / 2)
	{
		return true;
	}

	return false;
}