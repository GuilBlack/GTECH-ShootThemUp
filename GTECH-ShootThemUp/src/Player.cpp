#include "pch.h"
#include "Player.h"
#include "Game.h"

void Player::OnInit(sf::Vector2f position, bool isFriendly)
{
	Entity::OnInit(position, isFriendly);
	m_Health = 20;
	m_HealthBar.setSize(sf::Vector2f(m_Health * 5.f, 10.f));
	m_HealthBar.setPosition(sf::Vector2f(5.f, 5.f));
	m_Color = sf::Color::Magenta;
	m_Radius = 15.f;
	m_Speed = Game::GetGame().GetWindow()->getSize().x / 2.f;
	m_Direction = sf::Vector2f(0.f, 0.f);
	m_IsFriendly = true;
}



void Player::HandleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_ShootTimer = 0.f;
		}
	}
}

void Player::OnUpdate(float deltaTime)
{
	if (GetAsyncKeyState('A') < 0)
	{
		m_Direction.x = -1.f;
	}
	if (GetAsyncKeyState('D') < 0)
	{
		m_Direction.x = 1.f;
	}
	if (GetAsyncKeyState('W') < 0)
	{
		m_Direction.y = -1.f;
	}
	if (GetAsyncKeyState('S') < 0)
	{
		m_Direction.y = 1.f;
	}
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		if (m_ShootTimer > 0.2f)
		{
			m_ShootTimer -= 0.2f;
           	sf::Vector2f projectilePos = sf::Vector2f(m_Position.x, m_Position.y + 5.f);
			Game::GetGame().GetEntityManager()->CreateEntity(EntityID::Projectile, projectilePos, true);
		}
		else
		{
			m_ShootTimer += deltaTime;
		}
	}

	Move(deltaTime);
	if (m_Position.x < 0)
	{
		m_Position.x = 0;
	}
	if (m_Position.y < 0)
	{
		m_Position.y = 0;
	}
	if (m_Position.x + m_Radius * 2 > Game::GetGame().GetWindow()->getSize().x)
	{
		m_Position.x = Game::GetGame().GetWindow()->getSize().x - m_Radius * 2;
	}
	if (m_Position.y + m_Radius * 2 > Game::GetGame().GetWindow()->getSize().y)
	{
		m_Position.y = Game::GetGame().GetWindow()->getSize().y - m_Radius * 2;
	}
	m_Direction = sf::Vector2f(0.f, 0.f);
}

void Player::OnRender(std::unique_ptr<sf::RenderWindow>& window)
{
	Entity::OnRender(window);
	m_HealthBar.setSize(sf::Vector2f(20 * 10.f, 15.f));
	m_HealthBar.setFillColor(sf::Color::Red); 
	window->draw(m_HealthBar);
	m_HealthBar.setSize(sf::Vector2f(m_Health * 10.f, 15.f));
	m_HealthBar.setFillColor(sf::Color::Green); 
	window->draw(m_HealthBar);
}
