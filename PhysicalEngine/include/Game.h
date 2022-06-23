#pragma once

class Game
{
private:


public:
	Game();
	~Game();
	bool GameLoop();
};

Game::Game()
{
}

Game::~Game()
{
}

bool Game::GameLoop()
{

	return EXIT_SUCCESS;
}