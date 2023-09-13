#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	virtual void OnInit(sf::Vector2f position, bool isFriendly = false) override;
	virtual bool IsEnemy() override { return true; }
	virtual void OnUpdate(float deltaTime) override;
	
private:
	float m_ShootTimer = 0.f;
	float m_TimeBeforeChangeDirection = 0.f;
	float m_TimeBeforeChangeDirectionMax = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.f - 3.f)));
};

