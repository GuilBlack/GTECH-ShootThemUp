#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	virtual void OnInit(sf::Vector2f position, bool isFriendly = true) override;
	virtual void HandleInput(sf::Event event) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual bool IsPlayer() override { return true; }
	virtual void OnRender(std::unique_ptr<sf::RenderWindow>& window) override;
	virtual void IncreaseScore() override { ++m_KillCouns; }

private:
	float m_ShootTimer = 0.f;
	int m_KillCouns = 0;
	sf::RectangleShape m_HealthBar = sf::RectangleShape();
	sf::Text m_ScoreDisplay = sf::Text();
};

