#include "pch.h"
#include "Rock.h"

void Rock::OnInit(sf::Vector2f position, bool isFriendly)
{
	Entity::OnInit(position, isFriendly);
	m_Radius = 10.f;
	m_Color = sf::Color::White;
	m_Health = 1;
}

void Rock::OnUpdate(float deltaTime)
{
	Move(deltaTime);
	if (m_Position.y < 0.f - m_Radius * 2)
		m_IsDead = true;
}
