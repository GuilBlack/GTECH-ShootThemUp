#pragma once
#include "EntityManager.h"

class Game
{
public:
	Game() {}
	void Init();
	void Run();
	const std::unique_ptr<sf::RenderWindow>& GetWindow() const { return m_Window; }
	std::unique_ptr<EntityManager>& GetEntityManager() { return m_EntityManager; }

	inline static Game& GetGame()
	{
		static Game game;
		return game;
	}

private:
	bool m_IsRunning = true;
	float m_DeltaTime = 0.f;
	sf::Clock m_Clock = sf::Clock();
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<sf::RenderWindow> m_Window;

private:
	void Update();
	void Render();
	void HandleInput();
	void SpawnRocks();
	void SpawnEnemies();
};