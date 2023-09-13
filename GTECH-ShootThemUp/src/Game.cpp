#include "Game.h"

void Game::Init()
{
	m_EntityManager.reset(new EntityManager);
	m_Window.reset(new sf::RenderWindow(sf::VideoMode(1024, 768), "Shoot 'Em Up!"));
	m_EntityManager->CreateEntity(EntityID::Player, sf::Vector2f(1024 / 2, 0), true);
}

void Game::Run()
{
	srand((uint32_t)time(NULL));
	m_Clock.restart();
	while (m_Window->isOpen())
	{
		m_DeltaTime = m_Clock.restart().asSeconds();
		
		HandleInput();
		Update();
		Render();
	}
}

void Game::Update()
{
	SpawnRocks();
	SpawnEnemies();

	std::vector<Entity*>& entities = GetEntityManager()->GetEntities();
	for (int i = 0; i < entities.size(); ++i)
	{
		entities[i]->OnUpdate(m_DeltaTime);
	}

	for (int i = 0; i < entities.size(); ++i)
	{
		Entity* entity = entities[i];
		if (entity->IsPlayer())
		{
			for (int j = 0; j < entities.size(); ++j)
			{
				if (!entities[j]->IsFriendly())
				{
					entity->TestCollision(entities[j]);
				}
			}
		}
		if (entity->IsEnemy())
		{
			for (int j = 0; j < entities.size(); ++j)
			{
				if (entities[j]->IsFriendly())
				{
					entity->TestCollision(entities[j]);
				}
			}
		}
	}

	// PURGE
	auto it = GetEntityManager()->GetEntities().begin();
	while (it != GetEntityManager()->GetEntities().end())
	{
		if ((*it)->IsDead())
		{
			if ((*it)->IsPlayer())
			{
				++it;
				continue;
			}
			delete *it;
			*it = nullptr;
			it = GetEntityManager()->GetEntities().erase(it);
		}
		else
		{
			++it;
		}
	}

	if (m_EntityManager->GetPlayer()->IsDead())
	{
		m_Window->close();
	}
}

void Game::Render()
{
	sf::CircleShape shape;

	m_Window->clear();
	for (auto entity : m_EntityManager->GetEntities())
	{
		entity->OnRender(m_Window);
	}
	m_Window->display();
}

void Game::HandleInput()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window->close();
		if (m_EntityManager->GetPlayer())
			m_EntityManager->GetPlayer()->HandleInput(event);
	}
}

void Game::SpawnRocks()
{
	static float timer = 0.f;
	static float spawnRate = 5.f;
	timer += m_DeltaTime;
	if (timer >= spawnRate)
	{
		if (!(rand() % 4))
		{
			sf::Vector2f rockPos = sf::Vector2f(
				rand() % m_Window->getSize().x - 20.f, 
				(float)m_Window->getSize().y
			);
			m_EntityManager->CreateEntity(EntityID::Rock, rockPos, false);
		}
		timer -= .5f;
	}
}

void Game::SpawnEnemies()
{
	static float timer = 0.f;
	static float spawnRate = 1.f;
	timer += m_DeltaTime;
	if (timer >= spawnRate)
	{
		if (!(rand() % 4))
		{
			for (int i = 0; i < rand() % 3 + 3; ++i)
			{
				sf::Vector2f enemyPos = sf::Vector2f(
					rand() % m_Window->getSize().x - 25.f,
					(float)m_Window->getSize().y
				);
				m_EntityManager->CreateEntity(EntityID::Enemy, enemyPos, false);
			}
		}
		timer -= 1.f;
		spawnRate -= m_DeltaTime;
	}
}
