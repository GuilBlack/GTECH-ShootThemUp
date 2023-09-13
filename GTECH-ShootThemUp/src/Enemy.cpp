#include "pch.h"
#include "Enemy.h"
#include "Game.h"

void Enemy::OnInit(sf::Vector2f position, bool isFriendly)
{
	Entity::OnInit(position, isFriendly);
	m_Health = 1;
	m_Color = sf::Color::Yellow;
	m_Radius = 15.f;
	m_Speed = Game::GetGame().GetWindow()->getSize().x / (float)10.f;
}

void Enemy::OnUpdate(float deltaTime)
{
	m_TimeBeforeChangeDirection += deltaTime;
	if (m_TimeBeforeChangeDirection < m_TimeBeforeChangeDirectionMax || m_Position.x < 0 || m_Position.x > Game::GetGame().GetWindow()->getSize().x - m_Radius * 2)
	{
		m_Direction.x *= -1.f;
		m_TimeBeforeChangeDirection += deltaTime;
	}
	Move(deltaTime);

	if (m_ShootTimer > 1.f)
	{
		m_ShootTimer -= 1.f;
		sf::Vector2f projectilePos = sf::Vector2f(
			m_Position.x,
			m_Position.y - m_Radius - 2.f
		);
		Game::GetGame().GetEntityManager()->CreateEntity(EntityID::Projectile, projectilePos, false);
	}
	else
		m_ShootTimer += deltaTime;

	if (m_Position.y < 0.f - m_Radius * 2)
		m_IsDead = true;
}
