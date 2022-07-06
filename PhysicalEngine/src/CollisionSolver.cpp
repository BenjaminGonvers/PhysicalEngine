#include <CollisionSolver.h>

#include "RectangleBody.h"

CollisionSolver::CollisionSolver(std::vector<std::pair<RigidBody*, RigidBody*>> listToSolve) :_listToSolve(listToSolve)
{
}

CollisionSolver::~CollisionSolver()
{
}

void CollisionSolver::SolveCollisionList()
{
	for (auto Collision : _listToSolve)
	{
		auto* FirstCircleBody = dynamic_cast<CircleBody*>(Collision.first);
		auto* SegondCircleBody = dynamic_cast<CircleBody*>(Collision.second);

		if (FirstCircleBody != nullptr && SegondCircleBody != nullptr)
		{
			ResolveCircleCircle(FirstCircleBody, SegondCircleBody);
		}

		auto* firstRectangleBody = dynamic_cast<RectangleBody*>(Collision.first);
		auto* segondRectangleBody = dynamic_cast<RectangleBody*>(Collision.second);

		if (firstRectangleBody != nullptr != (segondRectangleBody != nullptr) && (FirstCircleBody != nullptr) != (SegondCircleBody != nullptr))
		{

			CircleBody* TCircleBody;
			RectangleBody* TRectangleBody;

			if (FirstCircleBody != nullptr)
				TCircleBody = FirstCircleBody;
			if (SegondCircleBody != nullptr)
				TCircleBody = SegondCircleBody;

			if (firstRectangleBody != nullptr)
				TRectangleBody = firstRectangleBody;
			if (segondRectangleBody != nullptr)
				TRectangleBody = segondRectangleBody;

			ResolveCircleRectangle(TCircleBody, TRectangleBody);
		}

		if (firstRectangleBody != nullptr && segondRectangleBody != nullptr)
		{
			ResolveRectangleRectangle(firstRectangleBody, segondRectangleBody);
		}
	}

}void CollisionSolver::ResolveCircleCircle(CircleBody* FirstCircleBody,CircleBody* SegondCircleBody)
{
	Vector2 vectorFirstToSegond = SegondCircleBody->getPosition() - FirstCircleBody->getPosition();
	float Phi = vectorFirstToSegond.GetAngularToOAxisX();
	float thetaV1 = FirstCircleBody->Velocity().GetAngularToOAxisX();
	float thetaV2 = SegondCircleBody->Velocity().GetAngularToOAxisX();
	float V1 = FirstCircleBody->Velocity().magnitude();
	float V2 = SegondCircleBody->Velocity().magnitude();
	float M1 = FirstCircleBody->Mass();
	float M2 = SegondCircleBody->Mass();


	float MinimalMouvement = FirstCircleBody->getDiameter() / 2 + SegondCircleBody->getDiameter() / 2 - vectorFirstToSegond.magnitude();
	SegondCircleBody->setPosition(SegondCircleBody->getPosition() + vectorFirstToSegond.normalized() * MinimalMouvement / 2);
	FirstCircleBody->setPosition(FirstCircleBody->getPosition() - vectorFirstToSegond.normalized() * MinimalMouvement / 2);

	Vector2 V1p;
	Vector2 V2p;

	V1p.x = (V1 * cos(thetaV1 - Phi) * (M1 - M2) + 2 * M2 * V2 * cos(thetaV2 - Phi)) / (M1 + M2) * cos(Phi) + V1 * sin(thetaV1 - Phi) * cos(Phi + std::numbers::pi / 2);
	V1p.y = (V1 * cos(thetaV1 - Phi) * (M1 - M2) + 2 * M2 * V2 * cos(thetaV2 - Phi)) / (M1 + M2) * sin(Phi) + V1 * sin(thetaV1 - Phi) * sin(Phi + std::numbers::pi / 2);

	V2p.x = (V2 * cos(thetaV2 - Phi) * (M2 - M1) + 2 * M1 * V1 * cos(thetaV1 - Phi)) / (M1 + M2) * cos(Phi) + V2 * sin(thetaV2 - Phi) * cos(Phi + std::numbers::pi / 2);
	V2p.y = (V2 * cos(thetaV2 - Phi) * (M2 - M1) + 2 * M1 * V1 * cos(thetaV1 - Phi)) / (M1 + M2) * sin(Phi) + V2 * sin(thetaV2 - Phi) * sin(Phi + std::numbers::pi / 2);

	FirstCircleBody->Velocity(V1p);
	SegondCircleBody->Velocity(V2p);
}

void CollisionSolver::ResolveRectangleRectangle(RectangleBody* FirstRectangleBody, RectangleBody* SegondRectangleBody)
{
	float firstMinX = std::min(std::min(FirstRectangleBody->aRelative().x, FirstRectangleBody->bRelative().x), std::min(FirstRectangleBody->cRelative().x, FirstRectangleBody->dRelative().x));
	float segondMinX = std::min(std::min(SegondRectangleBody->aRelative().x, SegondRectangleBody->bRelative().x), std::min(SegondRectangleBody->cRelative().x, SegondRectangleBody->dRelative().x));
	float firstMinY = std::min(std::min(FirstRectangleBody->aRelative().y, FirstRectangleBody->bRelative().y), std::min(FirstRectangleBody->cRelative().y, FirstRectangleBody->dRelative().y));
	float segondMinY = std::min(std::min(SegondRectangleBody->aRelative().y, SegondRectangleBody->bRelative().y), std::min(SegondRectangleBody->cRelative().y, SegondRectangleBody->dRelative().y));
	float firstMaxX = std::max(std::max(FirstRectangleBody->aRelative().x, FirstRectangleBody->bRelative().x), std::max(FirstRectangleBody->cRelative().x, FirstRectangleBody->dRelative().x));
	float segondMaxX = std::max(std::max(SegondRectangleBody->aRelative().x, SegondRectangleBody->bRelative().x), std::max(SegondRectangleBody->cRelative().x, SegondRectangleBody->dRelative().x));
	float firstMaxY = std::max(std::max(FirstRectangleBody->aRelative().y, FirstRectangleBody->bRelative().y), std::max(FirstRectangleBody->cRelative().y, FirstRectangleBody->dRelative().y));
	float segondMaxY = std::max(std::max(SegondRectangleBody->aRelative().y, SegondRectangleBody->bRelative().y), std::max(SegondRectangleBody->cRelative().y, SegondRectangleBody->dRelative().y));

	float upY = segondMaxY - firstMinY;
	float downY = firstMaxY - segondMinY;
	float rightX = segondMaxX - firstMinX;
	float leftX = firstMaxX - segondMinX;

	float minimalOverlaps = std::min(std::min(upY, downY), std::min(leftX, rightX));
	if(upY == minimalOverlaps)
	{
		FirstRectangleBody->setPosition(Vector2(FirstRectangleBody->getPosition().x, FirstRectangleBody->getPosition().y + minimalOverlaps / 2));
		SegondRectangleBody->setPosition(Vector2(SegondRectangleBody->getPosition().x, SegondRectangleBody->getPosition().y - minimalOverlaps / 2));
		Vector2 segondVelocity = Vector2(SegondRectangleBody->Velocity().x, FirstRectangleBody->Velocity().y);
		FirstRectangleBody->Velocity(Vector2(FirstRectangleBody->Velocity().x, SegondRectangleBody->Velocity().y));
		SegondRectangleBody->Velocity(segondVelocity);
	}else if(downY == minimalOverlaps)
	{
		FirstRectangleBody->setPosition(Vector2(FirstRectangleBody->getPosition().x, FirstRectangleBody->getPosition().y - minimalOverlaps / 2));
		SegondRectangleBody->setPosition(Vector2(SegondRectangleBody->getPosition().x, SegondRectangleBody->getPosition().y + minimalOverlaps / 2));
		Vector2 segondVelocity = Vector2(SegondRectangleBody->Velocity().x, FirstRectangleBody->Velocity().y);
		FirstRectangleBody->Velocity(Vector2(FirstRectangleBody->Velocity().x, SegondRectangleBody->Velocity().y));
		SegondRectangleBody->Velocity(segondVelocity);

	}else if(rightX == minimalOverlaps)
	{
		FirstRectangleBody->setPosition(Vector2(FirstRectangleBody->getPosition().x + minimalOverlaps / 2, FirstRectangleBody->getPosition().y ));
		SegondRectangleBody->setPosition(Vector2(SegondRectangleBody->getPosition().x - minimalOverlaps / 2, SegondRectangleBody->getPosition().y));
		Vector2 segondVelocity = Vector2(FirstRectangleBody->Velocity().x, SegondRectangleBody->Velocity().y);
		FirstRectangleBody->Velocity(Vector2(SegondRectangleBody->Velocity().x, FirstRectangleBody->Velocity().y));
		SegondRectangleBody->Velocity(segondVelocity);
		

	}else if(leftX == minimalOverlaps)
	{
		FirstRectangleBody->setPosition(Vector2(FirstRectangleBody->getPosition().x - minimalOverlaps / 2, FirstRectangleBody->getPosition().y));
		SegondRectangleBody->setPosition(Vector2(SegondRectangleBody->getPosition().x + minimalOverlaps / 2, SegondRectangleBody->getPosition().y));
		Vector2 segondVelocity = Vector2(FirstRectangleBody->Velocity().x, SegondRectangleBody->Velocity().y);
		FirstRectangleBody->Velocity(Vector2(SegondRectangleBody->Velocity().x, FirstRectangleBody->Velocity().y));
		SegondRectangleBody->Velocity(segondVelocity);
	}
	

}

void CollisionSolver::ResolveCircleRectangle(CircleBody* tCircleBody, RectangleBody* tRectangleBody)
{
	Vector2 velocityCircle = Vector2(tCircleBody->Velocity());
	Vector2 velocityRectangle = Vector2(tRectangleBody->Velocity());

	Vector2 distanceAbs(abs(tRectangleBody->getPosition().x - tCircleBody->getPosition().x), abs(tRectangleBody->getPosition().y - tCircleBody->getPosition().y));
	
		if(tCircleBody->getPosition().x <= tRectangleBody->bRelative().x && tCircleBody->getPosition().x >= tRectangleBody->aRelative().x)
		{
			float overLaps = tCircleBody->getDiameter() / 2 + abs(tRectangleBody->b().y) - abs(tCircleBody->getPosition().y - tRectangleBody->getPosition().y);

			if(tRectangleBody->getPosition().y <= tCircleBody->getPosition().y)
			{
				tRectangleBody->setPosition(Vector2(tRectangleBody->getPosition().x, tRectangleBody->getPosition().y - overLaps/2));
				tCircleBody->setPosition(Vector2(tCircleBody->getPosition().x, tCircleBody->getPosition().y + overLaps/2));
			}
			else
			{
				tRectangleBody->setPosition(Vector2(tRectangleBody->getPosition().x, tRectangleBody->getPosition().y + overLaps/2));
				tCircleBody->setPosition(Vector2(tCircleBody->getPosition().x, tCircleBody->getPosition().y - overLaps/2));
			}

			velocityCircle.y = tRectangleBody->Velocity().y;
			velocityRectangle.y = tCircleBody->Velocity().y;
			tRectangleBody->Velocity(velocityRectangle);
			tCircleBody->Velocity(velocityCircle);

		}else if(tCircleBody->getPosition().y <= tRectangleBody->bRelative().y && tCircleBody->getPosition().y >= tRectangleBody->cRelative().y)
		{
			float overLaps = tCircleBody->getDiameter() / 2 + abs(tRectangleBody->b().x) - abs(tCircleBody->getPosition().x - tRectangleBody->getPosition().x);

			if (tRectangleBody->getPosition().x <= tCircleBody->getPosition().x)
			{
				tRectangleBody->setPosition(Vector2(tRectangleBody->getPosition().x - overLaps / 2, tRectangleBody->getPosition().y));
				tCircleBody->setPosition(Vector2(tCircleBody->getPosition().x + overLaps / 2, tCircleBody->getPosition().y));
			}
			else
			{
				tRectangleBody->setPosition(Vector2(tRectangleBody->getPosition().x + overLaps / 2, tRectangleBody->getPosition().y));
				tCircleBody->setPosition(Vector2(tCircleBody->getPosition().x - overLaps / 2, tCircleBody->getPosition().y));
			}

			velocityCircle.x = tRectangleBody->Velocity().x;
			velocityRectangle.x = tCircleBody->Velocity().x;
			tRectangleBody->Velocity(velocityRectangle);
			tCircleBody->Velocity(velocityCircle);
		}
		else
		{
			if (tRectangleBody->getPosition().x > tCircleBody->getPosition().x && tRectangleBody->getPosition().y < tCircleBody->getPosition().y)
			{
				ResolveCircleRectangleCorner(tCircleBody, tRectangleBody, tRectangleBody->aRelative());
			}
			else if (tRectangleBody->getPosition().x < tCircleBody->getPosition().x && tRectangleBody->getPosition().y < tCircleBody->getPosition().y)
			{
				ResolveCircleRectangleCorner(tCircleBody, tRectangleBody, tRectangleBody->bRelative());
			}
			else if (tRectangleBody->getPosition().x < tCircleBody->getPosition().x && tRectangleBody->getPosition().y > tCircleBody->getPosition().y)
			{
				ResolveCircleRectangleCorner(tCircleBody, tRectangleBody, tRectangleBody->cRelative());
			}
			else if (tRectangleBody->getPosition().x > tCircleBody->getPosition().x && tRectangleBody->getPosition().y > tCircleBody->getPosition().y)
			{
				ResolveCircleRectangleCorner(tCircleBody, tRectangleBody, tRectangleBody->dRelative());
			}
		}


}

void CollisionSolver::ResolveCircleRectangleCorner(CircleBody* circleBody,RectangleBody* rectangleBody,Vector2 corner)
{
	Vector2 vectorFirstToSegond = corner - circleBody->getPosition();
	float Phi = vectorFirstToSegond.GetAngularToOAxisX();
	float thetaV1 = circleBody->Velocity().GetAngularToOAxisX();
	float thetaV2 = rectangleBody->Velocity().GetAngularToOAxisX();
	float V1 = circleBody->Velocity().magnitude();
	float V2 = rectangleBody->Velocity().magnitude();
	float M1 = circleBody->Mass();
	float M2 = rectangleBody->Mass();


	float overLaps = circleBody->getDiameter() / 2  - vectorFirstToSegond.magnitude();
	rectangleBody->setPosition(rectangleBody->getPosition() + vectorFirstToSegond.normalized() * overLaps / 2);
	circleBody->setPosition(circleBody->getPosition() - vectorFirstToSegond.normalized() * overLaps / 2);

	Vector2 V1p;
	Vector2 V2p;

	V1p.x = (V1 * cos(thetaV1 - Phi) * (M1 - M2) + 2 * M2 * V2 * cos(thetaV2 - Phi)) / (M1 + M2) * cos(Phi) + V1 * sin(thetaV1 - Phi) * cos(Phi + std::numbers::pi / 2);
	V1p.y = (V1 * cos(thetaV1 - Phi) * (M1 - M2) + 2 * M2 * V2 * cos(thetaV2 - Phi)) / (M1 + M2) * sin(Phi) + V1 * sin(thetaV1 - Phi) * sin(Phi + std::numbers::pi / 2);

	V2p.x = (V2 * cos(thetaV2 - Phi) * (M2 - M1) + 2 * M1 * V1 * cos(thetaV1 - Phi)) / (M1 + M2) * cos(Phi) + V2 * sin(thetaV2 - Phi) * cos(Phi + std::numbers::pi / 2);
	V2p.y = (V2 * cos(thetaV2 - Phi) * (M2 - M1) + 2 * M1 * V1 * cos(thetaV1 - Phi)) / (M1 + M2) * sin(Phi) + V2 * sin(thetaV2 - Phi) * sin(Phi + std::numbers::pi / 2);

	circleBody->Velocity(V1p);
	rectangleBody->Velocity(V2p);
}
