#include "pch.h"
#include "Entity.h"
#include "Game.h"
#include "Player.h"

sf::CircleShape Entity::m_RenderBody = sf::CircleShape();

void Entity::OnInit(sf::Vector2f position, bool isFriendly)
{
	m_Position = position;
	m_Direction = sf::Vector2f(0.f, -1.f);
	m_Speed = Game::GetGame().GetWindow()->getSize().x / (float)4.f;
	m_IsFriendly = isFriendly;
}

void Entity::OnUpdate(float deltaTime)
{
	Move(deltaTime);
}

void Entity::OnRender(std::unique_ptr<sf::RenderWindow>& window)
{
	m_RenderBody.setRadius(m_Radius);
	m_RenderBody.setFillColor(m_Color);
	m_RenderBody.setPosition(m_Position);
	window->draw(m_RenderBody);
}

void Entity::TestCollision(Entity* entity)
{
	if (IsDead() || entity->IsDead())
		return;
	sf::Vector2f thisCenter = sf::Vector2f(m_Position.x + m_Radius, m_Position.y + m_Radius);
	sf::Vector2f otherCenter = sf::Vector2f(entity->m_Position.x + m_Radius, entity->m_Position.y + m_Radius);

	float distance = powf(otherCenter.x - thisCenter.x, 2.f) + powf(otherCenter.y - thisCenter.y, 2.f);
	if (distance < powf(m_Radius + entity->m_Radius, 2.f))
	{
		DecreaseHealth();
		entity->DecreaseHealth();
		if (IsEnemy())
			Game::GetGame().GetEntityManager()->GetPlayer()->IncreaseScore();
	}
}

void Entity::Move(float deltaTime)
{
	sf::Vector2f velocity = m_Direction * m_Speed * deltaTime;
	m_Position += velocity;
}

void Entity::DecreaseHealth()
{
	--m_Health;
	if (m_Health == 0)
	{
		m_IsDead = true;
	}
}
