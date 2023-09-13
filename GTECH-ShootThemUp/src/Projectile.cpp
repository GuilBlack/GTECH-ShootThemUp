#include "pch.h"
#include "Projectile.h"
#include "Game.h"

void Projectile::OnInit(sf::Vector2f position, bool isFriendly)
{
	m_Position = position;
	if (isFriendly)
	{
		m_Direction = sf::Vector2f(0.f, 1.f);
		m_Speed = Game::GetGame().GetWindow()->getSize().x / 2.f;
		m_Color = sf::Color::Cyan;
	}
	else
	{
		m_Direction = sf::Vector2f(0.f, -1.f);
		m_Speed = Game::GetGame().GetWindow()->getSize().x / 4.f;
		m_Color = sf::Color::Red;
	}
	m_Radius = 5.f;
	m_Health = 1;
	m_IsFriendly = isFriendly;
}

void Projectile::OnUpdate(float deltaTime)
{
	Move(deltaTime);

	if (m_Position.y > Game::GetGame().GetWindow()->getSize().y || m_Position.y < 0 - m_Radius * 2)
		m_IsDead = true;
}