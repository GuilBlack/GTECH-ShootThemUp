#pragma once
#include "Entity.h"
class Projectile :
    public Entity
{
public:
	virtual void OnInit(sf::Vector2f position, bool isFriendly = false) override;
	virtual bool IsFriendly() override { return m_IsFriendly; }
	virtual bool IsProjectile() override { return true; }
	virtual void OnUpdate(float deltaTime) override;
};

