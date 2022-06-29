#pragma once
#include <vector>
#include "RigidBody.h"
#include "Gravity.h"

class Game
{
private:

	sf::Clock _clock;
	float _deltaTime = 0;

	Gravity _gravity = Gravity();
	std::vector<std::unique_ptr<RigidBody>> entity;

	bool _leftClickTrue = false;
	bool _rightClickTrue = false;

public:


	bool GameLoop();

	void upDate();
	void draw(sf::RenderWindow&);

	float getNewDeltaTime();
};
