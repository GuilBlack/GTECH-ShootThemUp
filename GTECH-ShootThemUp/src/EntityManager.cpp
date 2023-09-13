#include "pch.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"
#include "Projectile.h"

EntityManager::~EntityManager()
{
    for (auto& entity : m_Entites)
    {
		delete entity;
		entity = nullptr;
	}
	m_Entites.clear();
	m_Player = nullptr;
}

void EntityManager::CreateEntity(EntityID entityID, sf::Vector2f pos, bool isFriendly = false)
{
    Entity* entity = nullptr;

    switch (entityID)
    {
        case EntityID::Player:
        {
            entity = new Player();
            m_Player = entity;
            break;
        }
        case EntityID::Enemy:
        {
            entity = new Enemy();
            break;
        }
        case EntityID::Rock:
        {
            entity = new Rock();
            break;
        }
        case EntityID::Projectile:
        {
            entity = new Projectile();
        }
    }
    assert(entity && "Entity is still nullptr");
    entity->OnInit(pos, isFriendly);
    m_Entites.push_back(entity);
}
