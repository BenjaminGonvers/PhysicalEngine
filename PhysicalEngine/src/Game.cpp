#include <Game.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CircleBody.h>



bool Game::GameLoop()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_leftClickTrue)
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			sf::Vector2f worldPosition = window.mapPixelToCoords(localPosition);

			entity.emplace_back(std::make_unique<RigidBody>(sf::Vector2i(worldPosition.x, worldPosition.y)));
			_leftClickTrue = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _leftClickTrue)
		{
			_leftClickTrue = false;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !_rightClickTrue)
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			sf::Vector2f worldPosition = window.mapPixelToCoords(localPosition);

			entity.emplace_back(std::make_unique<CircleBody>(sf::Vector2i(worldPosition.x,worldPosition.y), 20));
			_rightClickTrue = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && _rightClickTrue)
		{
			_rightClickTrue = false;
		}

		// Force Solver in update? probably
		//ToDo Collision Solver probably like this "CollisionSolver(CheckCollision[std::pair])" in one line
		//ToDo MoveSame that upward, SolveMove(SolveVelocity) need probably one, and only method. name SolveMove();
		//toDo upDatePhysique
		upDate();
		window.clear(sf::Color::Black);
		draw(window);
		window.display();
	}


	return EXIT_SUCCESS;
}

void Game::upDate()
{
	_deltaTime = getNewDeltaTime();
	_gravity.deltaTime = _deltaTime;
	_gravity.Update(entity);
	for (auto& rigid_body : entity)
	{
		rigid_body->update(_deltaTime);
	}
}

void Game::draw(sf::RenderWindow& window)
{
	for (auto& rigid_body : entity)
	{
		rigid_body->draw(window);
	}
}

float Game::getNewDeltaTime()
{
	const sf::Time elapsed = _clock.restart();
	return elapsed.asSeconds();
}