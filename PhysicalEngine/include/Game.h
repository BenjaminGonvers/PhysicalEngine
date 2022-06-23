#pragma once
#include <vector>
#include <RigidBody.h>

class Game
{
private:
	std::vector<std::unique_ptr<RigidBody>> entity;

	bool _leftClickTrue = false;
	bool _rightClickTrue = false;

public:
	
	bool GameLoop();


	void upDate();
	void draw(sf::RenderWindow&);
};
