#include <Game.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CircleBody.h>
#include <CollisionChecker.h>
#include "CollisionSolver.h"
#include "RectangleBody.h"
#include <QuadPartitioning.h>


bool Game::GameLoop()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
	


	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
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

			entity.emplace_back(std::make_unique<RectangleBody>(sf::Vector2f(worldPosition.x, worldPosition.y),100,50));
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

			entity.emplace_back(std::make_unique<CircleBody>(sf::Vector2f(worldPosition.x,worldPosition.y), 20));
			_rightClickTrue = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && _rightClickTrue)
		{
			_rightClickTrue = false;
		}

		if(!entity.empty())
		{
			
			QuadPartitioning quad_partitioning = QuadPartitioning(entity);
			quad_partitioning.CreateNode();
			CollisionChecker collision_checker = CollisionChecker();
			CollisionSolver Collision_solver = collision_checker.CreateList(quad_partitioning.CreateList());
			Collision_solver.SolveCollisionList();
			quad_partitioning.DebugDraw(window);
		}


		upDate();
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