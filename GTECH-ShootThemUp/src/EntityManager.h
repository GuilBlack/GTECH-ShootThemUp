#pragma once
#include "Entity.h"

enum class EntityID
{
	Player,
	Enemy,
	Rock,
	Projectile
};

class EntityManager
{
public:
	~EntityManager();
	void CreateEntity(EntityID entityID, sf::Vector2f pos, bool isFriendly);
	std::vector<Entity*>& GetEntities() { return m_Entites; }
	const std::vector<Entity*>& GetEntities() const { return m_Entites; }
	Entity* const GetPlayer() { return m_Player; }

private:
	Entity* m_Player;
	std::vector<Entity*> m_Entites;
};

