#pragma once
#include "Entity.h"
class Rock : public Entity
{
public:
	virtual void OnInit(sf::Vector2f position, bool isFriendly = false) override;
	virtual bool IsObstacle() override { return true; }
	virtual void OnUpdate(float deltaTime) override;
};

