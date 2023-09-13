#pragma once

class Entity
{
public:
	virtual ~Entity() {}
	virtual void OnInit(sf::Vector2f position, bool isFriendly = false);
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender(std::unique_ptr<sf::RenderWindow>& window);
	virtual void OnDestroy() {}
	virtual void IncreaseScore() {}
	virtual void HandleInput(sf::Event event) {}
	virtual void TestCollision(Entity* entity);

	sf::Vector2f GetPosition() const { return m_Position; }
	sf::Color GetColor() const { return m_Color; }
	float GetRadius() const { return m_Radius; }
	int GetHealth() { return m_Health; }

	virtual bool IsPlayer() { return false; }
	virtual bool IsEnemy() { return false; }
	virtual bool IsObstacle() { return false; }
	virtual bool IsProjectile() { return false; }
	virtual bool IsFriendly() { return m_IsFriendly; }
	inline bool IsDead() { return m_IsDead; }

protected:
	int m_Health;
	sf::Vector2f m_Position;
	sf::Color m_Color;
	float m_Radius = 0.f;
	sf::Vector2f m_Direction;
	float m_Speed = 5.f;
	bool m_IsDead = false;
	bool m_IsFriendly = false;
	static sf::CircleShape m_RenderBody;

protected:
	virtual void Move(float deltaTime);
	virtual void DecreaseHealth();
};

